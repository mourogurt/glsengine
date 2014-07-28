TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

INCLUDEPATH += /usr/local/include/backend/ \
              /usr/local/include/system/

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

OTHER_FILES += \
    vert.glsl \
    frag.glsl

shaders_copy.commands += $(COPY_DIR) $$PWD/vert.glsl $$OUT_PWD/; \
                         $(COPY_DIR) $$PWD/frag.glsl $$OUT_PWD/;
first.depends = $(first) shaders_copy
export(first.depends)
export(shaders_copy.commands)
QMAKE_EXTRA_TARGETS += first shaders_copy
