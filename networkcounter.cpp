/****************************************************************************
**
** Copyright (C) 2013 Jolla Ltd
** Contact: lorn.potter@jollamobile.com
**
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "networkcounter.h"
#include <connman-qt5/counter.h>
#include <QtCore>

NetworkCounter::NetworkCounter(QObject *parent) :
    QObject(parent)
{
    m_bytes = 0;

    counter = new Counter(this);

    connect(counter,SIGNAL(counterChanged(QString,QVariantMap,bool)),this,SLOT(counterChanged(QString,QVariantMap,bool)));
    connect(counter,SIGNAL(bytesReceivedChanged(quint64)),this,SLOT(bytesReceivedChanged(quint64)));
    connect(counter,SIGNAL(bytesTransmittedChanged(quint64)),this,SLOT(bytesTransmittedChanged(quint64)));
    connect(counter,SIGNAL(secondsOnlineChanged(quint32)),this,SLOT(secondsOnlineChanged(quint32)));
    connect(counter,SIGNAL(roamingChanged(bool)),SLOT(roamingChanged(bool)));

    counter->setRunning(true);
}

void NetworkCounter::counterChanged(const QString servicePath, const QVariantMap &counters,  bool roaming)
{
    QTextStream out(stdout);
    out << servicePath
        << (roaming ? "  roaming" : "  home")
        << "   bytes received: " << counters["RX.Bytes"].toUInt()
        << "   bytes transmitted: " << counters["TX.Bytes"].toUInt()
        << "   seconds: " << counters["Time"].toUInt()
        << endl;

    if (counters["TX.Bytes"].toUInt() > 0) {
        qreal mbps = (qreal)((counters["TX.Bytes"].toUInt()*8 - m_bytes*8)/1024.0/1024.0);
        out << "Mbit/s: " << mbps << endl;
        m_bytes = counters["TX.Bytes"].toUInt();
    } else {
        m_bytes = 0;
    }
}

void NetworkCounter::bytesReceivedChanged(quint64 bytesRx)
{
    QTextStream out(stdout);
    out  << Q_FUNC_INFO << " " << bytesRx << endl;
}

void NetworkCounter::bytesTransmittedChanged(quint64 bytesTx)
{
    QTextStream out(stdout);
    out  << Q_FUNC_INFO << " " << bytesTx << endl;
}

void NetworkCounter::secondsOnlineChanged(quint32 seconds)
{
    QTextStream out(stdout);
    out << Q_FUNC_INFO << " " << seconds << endl;
}

void NetworkCounter::roamingChanged(bool roaming)
{
    QTextStream out(stdout);
    out  << Q_FUNC_INFO << " " << roaming << endl;
}
