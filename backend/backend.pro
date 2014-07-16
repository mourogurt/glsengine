TEMPLATE = lib
CONFIG += staticlib
INCLUDEPATH = ./include
INCLUDEPATH += ../system/include
HEADERS = ./include/engInit.hpp \
    ./include/engCustomShader.hpp \
    ./include/engScene.hpp \
    ./include/engValue.hpp \
    ./include/engBuffer.hpp
SOURCES = ./src/engInit.cpp \
    ./src/engCustomShader.cpp \
    ./src/engScene.cpp \
    ./src/engValue.cpp \
    ./src/engBuffer.cpp
QMAKE_CXXFLAGS += -std=c++11
#DEFINES += ENG_USE_CL

OTHER_FILES += \
    ../docs/roadmap.txt

CONFIG(debug, debug|release){
    DEFINES += _DEBUG
    DESTDIR = ../debug/lib
}
CONFIG(release, debug|release){
    DESTDIR = ../release/lib
}
