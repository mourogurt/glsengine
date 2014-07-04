TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH = ../../system
unix: LIBPATH = ../../system
win32 {
    CONFIG(debug, debug|release){
        LIBPATH = ../../system/debug
    }
    CONFIG(release, debug|release){
        LIBPATH = ../../system/release
    }
}

SOURCES += main.cpp

LIBS += -lsystem
QMAKE_CXXFLAGS += -std=c++11

include(deployment.pri)
qtcAddDeployment()

