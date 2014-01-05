TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH = ../backend \
              ../system
LIBPATH = ../backend \
          ../system

SOURCES += main.cpp

OTHER_FILES += \
    backend/hello.cl

HEADERS += \
    backend/engInit.hpp

LIBS += -lbackend -lsystem
QMAKE_CXXFLAGS += -std=c++11
unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += glfw3
unix: PKGCONFIG += gl
unix: PKGCONFIG += glew
unix|win32: LIBS += -lOpenCL
