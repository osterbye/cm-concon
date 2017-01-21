#ifndef OFONOHANDLER_H
#define OFONOHANDLER_H

#include <QObject>

class Modem;
class QOfonoManager;

class OfonoHandler : public QObject
{
    Q_OBJECT
public:
    explicit OfonoHandler(QObject *parent = 0);

private:
    //void turnOnModem(const QString &modemPath);
    void addModem(const QString &modem);
    void removeModem(const QString &modem);

private slots:
    void managerAvailableChanged(bool available);
    void managerModemAdded(const QString &modem);
    void managerModemRemoved(const QString &modem);

private:
    QOfonoManager *m_manager;
    QList<Modem*> m_modems;
};

#endif // OFONOHANDLER_H
