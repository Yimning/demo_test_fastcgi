#ENCRYPT_DISABLE=1
INCLUDES=. ${TOPDIR}/rtuwgfcgi/include ${TOPDIR}/ ${TOPDIR}/xlslib/ ${TOPDIR}/rtuwgfcgi/upgrade/ ${TOPDIR}/rtuwgfcgi/camera/ ${TOPDIR}/rtuwgfcgi/devmcu/ ${TOPDIR}/rtuwgfcgi/debug/  ${TOPDIR}/rtuwgfcgi/qdecoder/


lib=rtuwgfcgi
EXT_CFLAGS=-D_GNU_SOURCE -D_RTUWGFCGI_CLI_
ifndef ENCRYPT_DISABLE
#EXT_CFLAGS+=-D_ENCRYPT_ENABLE_
endif

include ${TOPDIR}/make/Make.build
include ${TOPDIR}/make/Make.lib