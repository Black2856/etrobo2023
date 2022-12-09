mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS +=\
   app.o \
   LineTracer.o \
   test.o \

APPL_LIBS += -lm

APPL_DIRS += \
   $(mkfile_path)LineTracer \
   $(mkfile_path)test \

INCLUDES += \
   -I$(mkfile_path)test \
   -I$(mkfile_path)LineTracer \
	
