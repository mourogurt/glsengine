TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH = ../backend \
              ../system
LIBPATH = ../backend \
          ../system

SOURCES += main.cpp

HEADERS += \
    backend/engInit.hpp

LIBS += -lbackend -lsystem
QMAKE_CXXFLAGS += -std=c++11
unix|win32: LIBS += -lGL -lGLEW -lglfw

include(deployment.pri)
qtcAddDeployment()

OTHER_FILES += \
    vshader.glsl \
    fshader.glsl

