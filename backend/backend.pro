TEMPLATE = lib
CONFIG += staticlib
HEADERS = engInit.hpp \
    engRender.hpp \
    engObject.hpp
SOURCES = engInit.cpp \
    engRender.cpp \
    engObject.cpp
QMAKE_CXXFLAGS += -std=c++11

