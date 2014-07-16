TEMPLATE = lib
CONFIG += staticlib
INCLUDEPATH = ./include
HEADERS = ./include/concurent_queue.hpp \
	  ./include/log.hpp
SOURCES = ./src/concurent_queue.cpp \
	  ./src/log.cpp
QMAKE_CXXFLAGS += -std=c++11

CONFIG(debug, debug|release){
    DESTDIR = ../debug/lib
}
CONFIG(release, debug|release){
    DESTDIR = ../release/lib
}
