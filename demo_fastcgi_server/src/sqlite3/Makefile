LIB_NAME = libsqlite3

PROJECT_ROOT_PATH = .
VERSION     =3.41.2

CCSRCS	= $(wildcard *.c)
CCOBJS = $(patsubst %.c,%.o, $(CCSRCS))

CC = gcc
DEBUG   =-DUSE_DEBUG
CFLAGS  =-Wall
AR = ar
ARFLAGS = -rv
SOFLAGS = -shared  -fPIC

INCPATH += -I$(PROJECT_ROOT_PATH) 


LDFLAGS += -L.
LDFLAGS += -ldl
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
