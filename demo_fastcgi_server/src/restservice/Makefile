LIB_NAME = restservice

PROJECT_ROOT_PATH = .
VERSION     = 13.0.0

CCSRCS	= $(wildcard *.c)
CCOBJS = $(patsubst %.c,%.o, $(CCSRCS))

CC = gcc
DEBUG   =-DUSE_DEBUG
CFLAGS  =-Wall
AR = ar
ARFLAGS = -rv
SOFLAGS = -shared  -fPIC

INCPATH += -I$(PROJECT_ROOT_PATH) 
INCPATH += -I/home/yimning/FastCGI/fcgi2-2.4.2/_install/include 
INCPATH += -I/home/yimning/FastCGI/json-c
INCPATH += -lfcgi   -ljson-c            #-lfcgi++ 
INCPATH += -I../src/debug

LDFLAGS += -L/home/yimning/FastCGI/fcgi2-2.4.2/_install/lib -L/home/yimning/FastCGI/json-c/_install
LIB_NAMES =  
TARGET_AR = 1
TARGET_SO = 1

#links
ifdef TARGET_SO
	TARGET = $(LIB_NAME).$(VERSION).so
endif

ifdef TARGET_AR
	TARGET = $(LIB_NAME).$(VERSION).a
endif

ifdef TARGET_SO
$(TARGET): $(CCOBJS)
	$(CC) $(SOFLAGS) $^ -o $@ $(LDFLAGS) $(LIB_NAMES)
endif

ifdef TARGET_AR
$(TARGET):$(CCOBJS)
	$(AR) $(ARFLAGS) $@ $^
endif

#compile
$(CCOBJS): %.o: %.c
	$(CC) $(SOFLAGS) $(INCPATH) $(CFLAGS) -c $< -o $@
	
.PHONY: install
install:
	mkdir -p $(PROJECT_ROOT_PATH)/lib
	cp $(TARGET) $(PROJECT_ROOT_PATH)/lib
	
.PHONY: clean
clean:
	@echo "Remove linked and compiled files......"
	-rm -rf $(CCOBJS)
	-rm -rf $(TARGET)
