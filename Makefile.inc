mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS +=\
   util.o \
   app.o \

APPL_LIBS += -lm

APPL_DIRS += \

INCLUDES += \
	
