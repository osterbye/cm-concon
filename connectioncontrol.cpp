#include "connectioncontrol.h"
#include "ofonohandler.h"

ConnectionControl::ConnectionControl(QObject *parent) : QObject(parent)
{
    m_ofono = new OfonoHandler(this);
}
