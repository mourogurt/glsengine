TEMPLATE = lib
CONFIG += staticlib
HEADERS = engInit.hpp \
    engCustomShader.hpp \
    engScene.hpp \
    engValue.hpp \
    engBuffer.hpp
SOURCES = engInit.cpp \
    engCustomShader.cpp \
    engScene.cpp \
    engValue.cpp \
    engBuffer.cpp
QMAKE_CXXFLAGS += -std=c++11
#DEFINES += ENG_USE_CL

OTHER_FILES += \
    ../docs/roadmap.txt

CONFIG(debug, debug|release){
    DEFINES += _DEBUG
}
