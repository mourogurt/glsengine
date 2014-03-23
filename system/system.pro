TEMPLATE = lib
CONFIG += staticlib
HEADERS = concurent_queue.h \
	  log.h
SOURCES = concurent_queue.cpp \
	  log.cpp
QMAKE_CXXFLAGS += -std=c++11
