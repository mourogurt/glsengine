TEMPLATE = lib
CONFIG += staticlib
HEADERS = engInit.hpp
SOURCES = engInit.cpp
QMAKE_CXXFLAGS += -std=c++11

OTHER_FILES += \
    ../docs/roadmap.txt

