TEMPLATE = lib
CONFIG += staticlib
HEADERS = engInit.hpp \
    engCustomShader.hpp \
    engData.hpp
SOURCES = engInit.cpp \
    engCustomShader.cpp \
    engData.cpp
QMAKE_CXXFLAGS += -std=c++11
#DEFINES += ENG_USE_CL

OTHER_FILES += \
    ../docs/roadmap.txt

