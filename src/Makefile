#ENCRYPT_DISABLE=1
INCLUDES=. ${TOPDIR}/src/include ${TOPDIR}/ ${TOPDIR}/xlslib/ ${TOPDIR}/src/upgrade/ ${TOPDIR}/src/camera/ ${TOPDIR}/src/devmcu/ ${TOPDIR}/src/debug/  ${TOPDIR}/src/qdecoder/


lib=src
EXT_CFLAGS=-D_GNU_SOURCE -D_src_CLI_
ifndef ENCRYPT_DISABLE
#EXT_CFLAGS+=-D_ENCRYPT_ENABLE_
endif

include ${TOPDIR}/make/Make.build
include ${TOPDIR}/make/Make.lib