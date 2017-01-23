#include "ofonohandler.h"
#include "modem.h"
#include <qofonoconnectioncontext.h>
#include <qofonoconnectionmanager.h>
#include <qofonomanager.h>
#include <qofonomodem.h>

#include <QDebug>

OfonoHandler::OfonoHandler(QObject *parent) : QObject(parent)
{
    m_manager = new QOfonoManager(this);
    connect(m_manager, SIGNAL(availableChanged(bool)), this, SLOT(managerAvailableChanged(bool)));
    connect(m_manager, SIGNAL(modemAdded(QString)), this, SLOT(managerModemAdded(QString)));
    connect(m_manager, SIGNAL(modemRemoved(QString)), this, SLOT(managerModemRemoved(QString)));
    managerAvailableChanged(m_manager->available());
}

/*void OfonoHandler::turnOnModem(const QString &modemPath)
{
    qDebug() << "Trying to turn on modem: " << modemPath;
    QOfonoModem modem;
    modem.setModemPath(modemPath);

    if (!modem.isValid()) {
        qWarning("Failed to validate modem: %s", qUtf8Printable(modemPath));
        return;
    }

    if (!modem.powered()) {
        qDebug() << "modem was not powered";
        modem.setPowered(true);
    }

    if (!modem.online()) {
        qDebug() << "modem was not online";
        modem.setOnline(true);
    }

    QOfonoConnectionManager connman;
    connman.setModemPath(modemPath);

    if (!connman.isValid()) {
        qWarning("Failed to validate connection manager for: %s", qUtf8Printable(modemPath));
        return;
    }

    if (!connman.powered()) {
        qDebug() << "connman was not powered";
        connman.setPowered(true);
    }

    qDebug() << "Connection context count is: " << connman.contexts().count();

    Q_FOREACH(const QString &path, connman.contexts()) {
        QOfonoConnectionContext connContext;
        connContext.setContextPath(path);
        if (connContext.isValid()) {
            if (connContext.type().compare("internet")) {
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

    qDebug() << "Modem " << modem.modemPath() << ". Powered: " << modem.powered() << ". Online: " << modem.online() << ".";
}*/

void OfonoHandler::managerAvailableChanged(bool available)
{
    if (available) {
        // For now, always turn on all modems
        QStringList modems = m_manager->modems();
        qDebug() << "modems: " << modems.size();
        for (int i = 0; i < modems.size(); ++i) {
            managerModemAdded(modems.at(i));
        }
    }
}

void OfonoHandler::managerModemAdded(const QString &modem)
{
    qDebug() << "Modem added: "<< modem;
    // For now, always turn on all modems
    //turnOnModem(modem);
    bool modemAlreadyExists = false;
    for (int i = 0; i < m_modems.size(); ++i) {
        if (m_modems.at(i)->path().compare(modem)) {
            modemAlreadyExists = true;
            break;
        }
    }
    if (!modemAlreadyExists) {
        m_modems.append(new Modem(modem, this));
        // For now, always turn on all modems
        m_modems.last()->activateInternetContext();
    }
}

void OfonoHandler::managerModemRemoved(const QString &modem)
{
    qDebug() << "Modem removed: "<< modem;
    for (int i = 0; i < m_modems.size(); ++i) {
        if (m_modems.at(i)->path().compare(modem)) {
            m_modems.removeAt(i);
            break;
        }
    }
}
