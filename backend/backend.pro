TEMPLATE = lib
CONFIG += staticlib
HEADERS = engInit.hpp \
    engRender.hpp
SOURCES = engInit.cpp \
    engRender.cpp
QMAKE_CXXFLAGS += -std=c++11

