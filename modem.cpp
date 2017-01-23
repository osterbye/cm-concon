#include "modem.h"
#include <qofonoconnectioncontext.h>
#include <qofonoconnectionmanager.h>
#include <qofonomodem.h>

#include <QDebug>

Modem::Modem(const QString &modem, QObject *parent) : QObject(parent)
{
    m_state = modem_state::DISCONNECTED;
    m_waitForModemPowered = false;
    m_waitForModemOnline = false;
    m_waitForConnManPowered = false;

    m_modem = new QOfonoModem(this);
    connect(m_modem, SIGNAL(poweredChanged(bool)), this, SLOT(modemPoweredChanged(bool)));
    connect(m_modem, SIGNAL(onlineChanged(bool)), this, SLOT(modemOnlineChanged(bool)));
    m_modem->setModemPath(modem);

    m_connMan = new QOfonoConnectionManager(this);
    connect(m_connMan, SIGNAL(poweredChanged(bool)), this, SLOT(connmanPoweredChanged(bool)));
    m_connMan->setModemPath(modem);
}

QString Modem::path() const
{
    return m_modem->modemPath();
}

bool Modem::activateInternetContext()
{
    while (!m_modem->isValid()) {
        // TODO: add timeout
        QCoreApplication::processEvents();
    }

    if (!m_modem->powered()) {
        qDebug() << "modem not powered... " << "Modem valid: " << m_modem->isValid() << ". Modem path: " << m_modem->modemPath();
        m_waitForModemPowered = true;
        m_modem->setPowered(true);
    } else {
        setModemOnline(true);
    }
    return true;
}

void Modem::modemPoweredChanged(bool powered)
{
    qDebug() << "modem power change: " << powered;
    if (powered && m_waitForModemPowered) {
        m_waitForModemPowered = false;
        setModemOnline(true);
    }
}

void Modem::modemOnlineChanged(bool online)
{
    if (online && m_waitForModemOnline) {
        m_waitForModemOnline = false;
        setConnManPower(true);
    }
}

void Modem::connmanPoweredChanged(bool powered)
{
    if (powered && m_waitForConnManPowered) {
        m_waitForConnManPowered = false;
        setInternetContextActive(true);
    }
}

void Modem::setModemOnline(bool online)
{
    if (online) {
        if (!m_modem->online()) {
            m_waitForModemOnline = true;
            m_modem->setOnline(true);
        } else {
            setConnManPower(true);
        }
    } else {
        m_modem->setOnline(false);
    }
}

void Modem::setConnManPower(bool power)
{
    while (!m_connMan->isValid()) {
        // TODO: add timeout
        QCoreApplication::processEvents();
    }
    qDebug() << "ConnMan is valid";

    if (power) {
        if (!m_connMan->powered()) {
            m_waitForConnManPowered = true;
            m_connMan->setPowered(true);
        } else {
            setInternetContextActive(true);
        }
    } else {
        m_connMan->setPowered(false);
    }
}

void Modem::setInternetContextActive(bool active)
{
    if (active) {
        qDebug() << "Connection context count is: " << m_connMan->contexts().count();

        Q_FOREACH(const QString &path, m_connMan->contexts()) {
            QOfonoConnectionContext connContext;
            connContext.setContextPath(path);
            while (!connContext.isValid()) {
                // TODO: add timeout
                QCoreApplication::processEvents();
            }
            if (connContext.isValid()) {
                qDebug() << "Context type: " << connContext.type();
                if (connContext.type() == "internet") {
                    if (!connContext.active()) {
                        connContext.setActive(true);
                    } else {
                        qDebug() << "Connection context for internet is already active";
                    }
                } else {
                    qDebug() << "Connection context is not internet but " << connContext.type();
                }
            } else {
                qDebug() << "Connection context " << path << " is not valid!";
            }
        }
    }
    qDebug() << "Modem " << m_modem->modemPath() << ". Powered: " << m_modem->powered() << ". Online: " << m_modem->online() << ".";
}
