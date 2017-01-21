#include <QCoreApplication>
#include "connectioncontrol.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ConnectionControl concon(&a);
    return a.exec();
}
