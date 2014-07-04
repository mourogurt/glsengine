TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH = ../../backend \
              ../../system
unix: LIBPATH = ../../backend \
          ../../system
win32 {
    CONFIG(debug, debug|release){
        LIBPATH = ../../backend/debug \
                  ../../system/debug
    }
    CONFIG(release, debug|release){
        LIBPATH = ../../backend/release \
                  ../../system/release
    }
}

SOURCES += main.cpp

LIBS += -lbackend -lsystem
QMAKE_CXXFLAGS += -std=c++11
win32: LIBS += -lopengl32 -lGLEW -lglfw3
unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += gl
    PKGCONFIG += glew
    PKGCONFIG += glfw3
}
include(deployment.pri)
qtcAddDeployment()

