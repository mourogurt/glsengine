TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    engInit.cpp \
    engModel.cpp \
    engCompute.cpp \
    engCamera.cpp

QMAKE_CXXFLAGS += -std=c++11
unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += glfw3
unix: PKGCONFIG += gl
unix: PKGCONFIG += glew
unix: PKGCONFIG += glu


HEADERS += \
    engInit.hpp \
    engModel.hpp \
    engCompute.hpp \
    engCamera.hpp

unix|win32: LIBS += -lOpenCL
unix|macx: LIBS += -lpthread

OTHER_FILES += \
    hello.cl \
    testModel \
    vertex.glsl \
    fragment.glsl
