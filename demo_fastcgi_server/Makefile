#!/bin/sh
export TOPDIR=$(shell pwd)
include ${TOPDIR}/make/Make.local
CPP=gcc
TARGET=fcgitest.fcgi
STATIC_LIBS =${TOPDIR}/src/libsrc.a \

#这里递归遍历3级子目录
DIRS := $(shell find ./src -maxdepth 3 -type d)

#这里循环遍历目录

SRC_FILES = $(foreach dir,$(DIRS),$(wildcard $(dir)))

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))

mkfile_dir := $(dir $(mkfile_path))
 
subdirs += src 
subdirs += src/debug 
subdirs += src/qdecoder 
subdirs += src/cJSON 
subdirs += src/restservice
subdirs += src/raphters

include ${TOPDIR}/make/Make.subdirs
include ${TOPDIR}/make/Make.build

all:  ${TARGET}_nostrip ${TARGET}

${TARGET}:${TARGET}_nostrip 
	${STRIP} ${TARGET}_nostrip -o $@


LIBS += -L/home/yimning/FastCGI/fcgi2-2.4.2/_install/lib
LIBS += -L/home/yimning/FastCGI/rudecgi-5.0.0/_install/lib   #后续删除
LIBS += -L/home/yimning/FastCGI/json-c/_install
LIBS += -L/home/yimning/FastCGI/lighttpd/www/demo_test_fastcgi/demo_fastcgi_server/src/lib


LIBS += -lfcgi  # -lfcgi++
LIBS += -lrudecgi  #后续删除
LIBS += -ljson-c
#LIBS += -lraphters
#LIBS += -lqdecoder

${TARGET}_nostrip:main.o ${STATIC_LIBS}
	cp -rf ${TOPDIR}/src/debug/dbgout.1.0.0.a ${TOPDIR}/src/lib/dbgout.a
	cp -rf ${TOPDIR}/src/qdecoder/qdecoder.1.0.0.a ${TOPDIR}/src/lib/qdecoder.a
	cp -rf ${TOPDIR}/src/cJSON/cJSON.1.0.0.a ${TOPDIR}/src/lib/cJSON.a
#	cp -rf ${TOPDIR}/src/restservice/restservice.13.0.0.a ${TOPDIR}/src/lib/restservice.a  
	cp -rf ${TOPDIR}/src/raphters/raphters.1.0.0.a  ${TOPDIR}/src/lib/raphters.a
	${CPP} main.o ${STATIC_LIBS} ${TOPDIR}/src/lib/* -lcrypt -lpthread -lm -lrt ${LIBS} -o $@
	
clean::
	rm  -rf *.o ${TARGET} ${TARGET}_nostrip

