TEMPLATE = lib
CONFIG += staticlib
INCLUDEPATH = ./include
INCLUDEPATH += ../system/include
HEADERS = ./include/engInit.hpp \
    ./include/engShader.hpp \
    ./include/engScene.hpp \
    ./include/engValue.hpp \
    ./include/engBuffer.hpp
SOURCES = ./src/engInit.cpp \
    ./src/engShader.cpp \
    ./src/engScene.cpp \
    ./src/engValue.cpp \
    ./src/engBuffer.cpp
QMAKE_CXXFLAGS += -std=c++11
#DEFINES += ENG_USE_CL

OTHER_FILES += \
    ../docs/roadmap.txt

CONFIG(debug, debug|release){
    DEFINES += _DEBUG
}

DESTDIR = ../lib

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
