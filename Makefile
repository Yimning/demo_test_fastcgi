#!/bin/sh
export TOPDIR=$(shell pwd)
include ${TOPDIR}/make/Make.local
CPP=g++
TARGET=fcgitest.fcgi
STATIC_LIBS =${TOPDIR}/src/libsrc.a \

subdirs = src src/qdecoder/

#          src/upgrade\
#          src/camera\
#          src/devmcu\

include ${TOPDIR}/make/Make.subdirs
include ${TOPDIR}/make/Make.build

all:  ${TARGET}_nostrip ${TARGET}

${TARGET}:${TARGET}_nostrip 
	${STRIP} ${TARGET}_nostrip -o $@

LIBS += -L/home/yimning/FastCGI/fcgi2-2.4.2/_install/lib
LIBS += -L/home/yimning/FastCGI/rudecgi-5.0.0/_install/lib
LIBS += -lfcgi++ -lfcgi
LIBS += -lrudecgi

${TARGET}_nostrip:main.o ${STATIC_LIBS}
	cp ${TOPDIR}/src/qdecoder/qdecoder.1.0.0.a ${TOPDIR}/src/qdecoder/qdecoder.a -rf
	${CPP} main.o ${STATIC_LIBS} ${TOPDIR}/src/qdecoder/qdecoder.a -lcrypt -lpthread -lm -lrt ${LIBS} -o $@
	
clean::
	rm  -rf *.o ${TARGET} ${TARGET}_nostrip

