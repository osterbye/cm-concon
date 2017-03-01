#ifndef CONNECTIONCONTROL_H
#define CONNECTIONCONTROL_H

#include <QObject>

class OfonoHandler;
class NetworkCounter;

class ConnectionControl : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionControl(QObject *parent = 0);

signals:

public slots:

private:
    OfonoHandler *m_ofono;
    NetworkCounter *m_counter;
};

#endif // CONNECTIONCONTROL_H
