#-------------------------------------------------
#
# Project created by QtCreator 2019-09-08T12:05:11
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MCU_Analysis
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

INCLUDEPATH += ./Idriver\
               ./CApp\
               ./CWinDesign\
               ./IDriver/usbhid

LIBS += -L$$_PRO_FILE_PWD_/IDriver/usbhid/\
        -lhidapi


HEADERS += \
    CApp/CAppDriver.h \
    CApp/CAppManagement.h \
    CApp/CConnectCenter.h \
    CWinDesign/CWAdminLogin.h \
    CWinDesign/CWTestTools.h \
    CWinDesign/CWTestToolsStatus.h \
    CWinDesign/MainWindow.h \
    IDriver/IDataStruct.h \
    IDriver/IUart.h \
    IDriver/IUdpServer.h \
    IDriver/IUsbHid.h \
    IDriver/usbhid/hidapi.h

SOURCES += \
    CApp/CAppManagement.cpp \
    CApp/CConnectCenter.cpp \
    CWinDesign/CWAdminLogin.cpp \
    CWinDesign/CWTestTools.cpp \
    CWinDesign/CWTestToolsStatus.cpp \
    CWinDesign/MainWindow.cpp \
    IDriver/IDataStruct.cpp \
    IDriver/IUart.cpp \
    IDriver/IUdpServer.cpp \
    IDriver/IUsbHid.cpp \
    main.cpp


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    CWinDesign/CWAdminLogin.ui \
    CWinDesign/CWTestTools.ui \
    CWinDesign/CWTestToolsStatus.ui \
    CWinDesign/MainWindow.ui




