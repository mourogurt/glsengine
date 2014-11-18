TEMPLATE = lib
CONFIG += staticlib
INCLUDEPATH = ./include
HEADERS = ./include/concurent_queue.hpp \
	  ./include/log.hpp
SOURCES = ./src/concurent_queue.cpp \
	  ./src/log.cpp
QMAKE_CXXFLAGS += -std=c++11

#DESTDIR = ../lib

copydata.commands = $(COPY_DIR) $$PWD/include $$OUT_PWD/../include/system
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
removedata.commands = rm -rf $$OUT_PWD/../include/system
clean.depends = $(clean) removedata
export(clean.depends)
export(removedata.commands)
QMAKE_EXTRA_TARGETS += clean removedata
