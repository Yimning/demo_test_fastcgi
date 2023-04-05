#ENCRYPT_DISABLE=1
INCLUDES +=. ${TOPDIR}/ ${TOPDIR}/src/include 
INCLUDES +=  ${TOPDIR}/xlslib/ ${TOPDIR}/src/upgrade/ ${TOPDIR}/src/camera/ ${TOPDIR}/src/devmcu/ 
INCLUDES +=  ${TOPDIR}/src/qdecoder/
INCLUDES +=  ${TOPDIR}/src/debug/
INCLUDES +=  ${TOPDIR}/src/cJSON/
INCLUDES +=  ${TOPDIR}/src/api/
INCLUDES +=  ${TOPDIR}/src/restservice/


lib=src
EXT_CFLAGS=-D_GNU_SOURCE -D_src_CLI_
ifndef ENCRYPT_DISABLE
#EXT_CFLAGS+=-D_ENCRYPT_ENABLE_
endif

include ${TOPDIR}/make/Make.build
include ${TOPDIR}/make/Make.lib