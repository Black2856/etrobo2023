mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS +=\
   util.o \
   Tracer.o \

APPL_LIBS += -lm

APPL_DIRS += \
   $(mkfile_path)app2 \

INCLUDES += \
   -I$(mkfile_path)app2 \
	
