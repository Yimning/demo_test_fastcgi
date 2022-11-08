#!/bin/sh
export TOPDIR=$(shell pwd)
include ${TOPDIR}/make/Make.local
CPP=g++
TARGET=fcgitest.fcgi
STATIC_LIBS =${TOPDIR}/rtuwgfcgi/librtuwgfcgi.a \

#STATIC_LIBS=${TOPDIR}/rtuwgfcgi/librtuwgfcgi.a \
	    ${TOPDIR}/rtuwgfcgi/upgrade/libupgrade.a\
	    ${TOPDIR}/rtuwgfcgi/camera/libcamera.a\
	    ${TOPDIR}/rtuwgfcgi/devmcu/libdevmcu.a\

			
#DYNAMIC_LIBS=${TOPDIR}/src/k37/protocol/libk37protocol.so \
#             ${TOPDIR}/src/k37/rep_protocol/libk37repprotocol.so \
#             ${TOPDIR}/src/k37/mon_protocol/libk37monprotocol.so
 
#STATIC_LIBS=${TOPDIR}/src/SerialDataMng/libSerialDataMng.a 
###NO ppclient######
#STATIC_LIBS+=${TOPDIR}/xlslib/libxls.a
#STATIC_LIBS+=${TOPDIR}/src/watchdog/libwtd.a	\
	 ${TOPDIR}/src/misc/libmisc.a		\
	 ${TOPDIR}/src/encrypt/encrypt.a 

#######switch static libaray######
#SWITCH_LIBS=${TOPDIR}/src/switch/sysinit/libsysinit.a \
			${TOPDIR}/src/switch/acl/libacl.a \
			${TOPDIR}/src/switch/igmpsnooping/libigmpsnoop.a \
			${TOPDIR}/src/switch/bridge/libbridge.a \
			${TOPDIR}/src/switch/route/libroute.a \
			${TOPDIR}/src/switch/cli/libcli.a \
			${TOPDIR}/src/switch/usermanage/libusermanage.a \
			${TOPDIR}/src/switch/dhcp82/libdhcp82.a \
			${TOPDIR}/src/switch/loopback/libloopback.a \
			${TOPDIR}/src/switch/mac/libmac.a \
			${TOPDIR}/src/switch/mirror/libmirror.a \
			${TOPDIR}/src/switch/port/libport.a \
			${TOPDIR}/src/switch/pppoe/libpppoe.a \
			${TOPDIR}/src/switch/qos/libqos.a \
			${TOPDIR}/src/switch/rstp/librstp.a \
			${TOPDIR}/src/switch/ssp/libssp.a \
			${TOPDIR}/src/switch/sys/libsys.a \
			${TOPDIR}/src/switch/timer/libtimer.a \
			${TOPDIR}/src/switch/vlan/liblinux_vlan.a \
			${TOPDIR}/src/switch/zip/libzip.a \
			${TOPDIR}/src/switch/oam/liboam.a \
			${TOPDIR}/src/ppclient/libppclient.a


####cli and usermanage are in directory switch, but don't remove them because
####they may ge used in future when it is no need to manage the switch.
####No ppclient now
#subdirs=cli usermanage SerialDataMng ppclient watchdog misc modules udhcp encrypt switch
#subdirs=SerialDataMng ppclient watchdog misc modules udhcp encrypt switch 
subdirs = rtuwgfcgi rtuwgfcgi/qdecoder/

#          rtuwgfcgi/upgrade\
#          rtuwgfcgi/camera\
#          rtuwgfcgi/devmcu\

include ${TOPDIR}/make/Make.subdirs
include ${TOPDIR}/make/Make.build

all:  ${TARGET}_nostrip ${TARGET}

${TARGET}:${TARGET}_nostrip 
	${STRIP} ${TARGET}_nostrip -o $@
#	cp ${TARGET} /opt/linux/k37/kernel/ramdisk/usr/
#	cp ${TARGET} /opt/linux/k37/kernel/rootfs/usr/
#	cp ${TARGET} /opt/rtu_wg/kernel/rootfs/opt/software/lighttpd-1.4.39/_install/cgi-bin/usr
#	cp ${TARGET} /opt/rtu_wg/kernel/ramdisk/opt/software/lighttpd-1.4.39/_install/cgi-bin/usr
#	cp ${TARGET} /opt/rtu_dosing/kernel/rootfs/usr/lighttpd-1.4.39/_install/cgi-bin/
#	cp ${TARGET} /opt/rtu_wg/kernel/ramdisk/usr/lighttpd-1.4.39/_install/cgi-bin/
#	cp ${TARGET} /tftpboot/ 

LIBS += -L/home/yimning/FastCGI/fcgi2-2.4.2/_install/lib
LIBS += -L/home/yimning/FastCGI/rudecgi-5.0.0/_install/lib
LIBS += -lfcgi++ -lfcgi
LIBS += -lrudecgi
	
#${TARGET}_nostrip:main.o ${STATIC_LIBS} ${SWITCH_LIBS} ${SWITCH_SDK_LIBS}  sys_init.o
#	${CC} main.o -lcrypt -lpthread -lm ${STATIC_LIBS}  ${SWITCH_LIBS} ${SWITCH_SDK_LIBS} -o $@
${TARGET}_nostrip:main.o ${STATIC_LIBS}
	cp ${TOPDIR}/rtuwgfcgi/upgrade/libupgrade.a.tengent ${TOPDIR}/rtuwgfcgi/upgrade/libupgrade.a
	cp ${TOPDIR}/rtuwgfcgi/devmcu/libdevmcu.a.tengent ${TOPDIR}/rtuwgfcgi/devmcu/libdevmcu.a
	cp ${TOPDIR}/rtuwgfcgi/camera/libcamera.a.tengent ${TOPDIR}/rtuwgfcgi/camera/libcamera.a
	cp ${TOPDIR}/rtuwgfcgi/qdecoder/qdecoder.1.0.0.a ${TOPDIR}/rtuwgfcgi/qdecoder/qdecoder.a
	${CPP} main.o ${STATIC_LIBS} ${TOPDIR}/rtuwgfcgi/qdecoder/qdecoder.a -lcrypt -lpthread -lm -lrt ${LIBS} -o $@
	
clean::
	rm  -rf *.o ${TARGET} ${TARGET}_nostrip

