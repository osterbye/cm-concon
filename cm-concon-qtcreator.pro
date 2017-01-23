# sysroot changes
!include(../local_conf.pri): error(local_conf.pri file not found)
QMAKE_CFLAGS -= --sysroot=$$[QT_SYSROOT]
QMAKE_CFLAGS += --sysroot=$${YOCTO_BUILD_DIR}/tmp/sysroots/apalis-imx6
QMAKE_CXXFLAGS -= --sysroot=$$[QT_SYSROOT]
QMAKE_CXXFLAGS += --sysroot=$${YOCTO_BUILD_DIR}/tmp/sysroots/apalis-imx6
QMAKE_LFLAGS -= --sysroot=$$[QT_SYSROOT]
QMAKE_LFLAGS += --sysroot=$${YOCTO_BUILD_DIR}/tmp/sysroots/apalis-imx6
INCLUDEPATH += $${YOCTO_BUILD_DIR}/tmp/sysroots/apalis-imx6/usr/include
INCLUDEPATH += $${YOCTO_BUILD_DIR}/tmp/sysroots/apalis-imx6/usr/include/qofono-qt5

include(cm-concon.pri)
