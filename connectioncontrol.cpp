#include "connectioncontrol.h"
#include "ofonohandler.h"
#include "networkcounter.h"

ConnectionControl::ConnectionControl(QObject *parent) : QObject(parent)
{
    m_ofono = new OfonoHandler(this);
    m_counter = new NetworkCounter(this);
}
