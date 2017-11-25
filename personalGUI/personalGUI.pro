#-------------------------------------------------
#
# Project created by QtCreator 2017-10-24T14:28:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = personalGUI
TEMPLATE = app

RPI_LIBS = ../raspberrypi_libs
LEPTONSDK = leptonSDKEmb32PUB

PRE_TARGETDEPS += sdk
QMAKE_EXTRA_TARGETS += sdk sdkclean
sdk.commands = make -C $${RPI_LIBS}/$${LEPTONSDK}
sdkclean.commands = make -C $${RPI_LIBS}/$${LEPTONSDK} clean

DEPENDPATH += .
INCLUDEPATH += . $${RPI_LIBS}

DESTDIR=.
OBJECTS_DIR=gen_objs
MOC_DIR=gen_mocs

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        headgui.cpp \
    ../Lepton/LeptonThread.cpp \
    ../Netzwerk/client/client.cpp \
    ../Netzwerk/User/User.cpp \
    ../I2C/DaTa/DaTa.cpp \
    ../I2C/I2C.cpp

HEADERS += \
        headgui.h \
    ../Lepton/LeptonThread.h \
    ../Netzwerk/client/client.h \
    ../Netzwerk/User/User.h \
    ../I2C/DaTa/DaTa.h \
    ../I2C/I2C.h

QMAKE_CXXFLAGS += -std=c++0x -pthread

LIBS += -pthread -lwiringPi

unix:LIBS += -L$${RPI_LIBS}/$${LEPTONSDK}/Debug -lLEPTON_SDK

unix:QMAKE_CLEAN += -r $(OBJECTS_DIR) $${MOC_DIR}
