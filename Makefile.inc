mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS +=\
   util.o \

APPL_LIBS += -lm

APPL_DIRS += \

INCLUDES += \
	
