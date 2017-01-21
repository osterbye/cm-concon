#ifndef CONNECTIONCONTROL_H
#define CONNECTIONCONTROL_H

#include <QObject>

class OfonoHandler;

class ConnectionControl : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionControl(QObject *parent = 0);

signals:

public slots:

private:
    OfonoHandler *m_ofono;
};

#endif // CONNECTIONCONTROL_H
