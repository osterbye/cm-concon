#ifndef MODEM_H
#define MODEM_H

#include <QObject>

class QOfonoConnectionManager;
class QOfonoModem;

class Modem : public QObject
{
    Q_OBJECT
public:
    explicit Modem(const QString &modem, QObject *parent = 0);

    QString path() const;
    bool activateInternetContext();

signals:

private slots:
    void modemPoweredChanged(bool powered);
    void modemOnlineChanged(bool online);
    void connmanPoweredChanged(bool powered);

private:
    void setModemOnline(bool online);
    void setConnManPower(bool power);
    void setInternetContextActive(bool active);

private:
    QOfonoModem *m_modem;
    QOfonoConnectionManager *m_connMan;

    enum modem_state{
        CONNECTING,
        CONNECTED,
        DISCONNECTING,
        DISCONNECTED
    };

    modem_state m_state;
    bool m_waitForModemPowered;
    bool m_waitForModemOnline;
    bool m_waitForConnManPowered;
};

#endif // MODEM_H
