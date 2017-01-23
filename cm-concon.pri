QT += core dbus
QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

TARGET = concond
TEMPLATE = app

LIBS +=  -lqofono-qt5

# files
SOURCES += main.cpp \
    connectioncontrol.cpp \
    ofonohandler.cpp \
    modem.cpp

HEADERS += \
    connectioncontrol.h \
    ofonohandler.h \
    modem.h

# install
target.path = /usr/bin
INSTALLS += target

