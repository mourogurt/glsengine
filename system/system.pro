TEMPLATE = lib
CONFIG += staticlib
HEADERS = concurent_queue.h \
	  log.h \
    contextmutex.hpp
SOURCES = concurent_queue.cpp \
	  log.cpp \
    contextmutex.cpp
QMAKE_CXXFLAGS += -std=c++11
