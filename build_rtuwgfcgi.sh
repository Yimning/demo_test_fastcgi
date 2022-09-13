#!/bin/sh

export TOPDIR=`pwd`


echo $TOPDIR

export CROSS_COMPILE=

make




cp rtuwg.fcgi ${TOPDIR}/lighttpd-1.4.39/_install/cgi-bin/ 
cd ${TOPDIR}
tar -czvf webserver.tgz lighttpd-1.4.39
cd -
#cp webserver.tgz /tftpboot/
cp webserver.tgz ${TOPDIR}/../tftpboot/

#cp lighttpd-1.4.39 /opt/rtu_t36s/kernel/rootfs/usr -rf
cp lighttpd-1.4.39 ${TOPDIR}/../../kernel/rootfs/usr -rf
#cp lighttpd-1.4.39 /opt/rtu_wg/kernel/ramdisk/usr -rf
#cp lighttpd-1.4.39 /opt/rtu_dosing/kernel/ramdisk/usr -rf

#cp rtuwg.fcgi /opt/rtu_wg/kernel/ramdisk/usr
#cp rtuwg.fcgi /opt/rtu_wg/kernel/rootfs/usr
