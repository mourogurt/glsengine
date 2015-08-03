TEMPLATE = lib
CONFIG += staticlib
CONFIG -= qt
INCLUDEPATH += ./include
INCLUDEPATH += ../system/include
HEADERS = ./include/engInit.hpp \
    include/engGLBufferAllocator.hpp \
    include/engGLTextureAllocator.hpp \
    include/engGLShaderAllocator.hpp
SOURCES = ./src/engInit.cpp \
    src/engGLBufferAllocator.cpp \
    src/engGLTextureAllocator.cpp \
    src/engGLShaderAllocator.cpp
QMAKE_CXXFLAGS += -std=c++11

OTHER_FILES += \
    ../docs/roadmap.txt

CONFIG(debug, debug|release){
    DEFINES += _DEBUG
}

copydata.commands = $(COPY_DIR) $$PWD/include $$OUT_PWD/../include/backend
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
removedata.commands = rm -rf $$OUT_PWD/../include/backend
clean.depends = $(clean) removedata
export(clean.depends)
export(removedata.commands)
QMAKE_EXTRA_TARGETS += clean removedata
