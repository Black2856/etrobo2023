mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS +=\
   LineTracer.o \
   test.o \
   app.o \

APPL_LIBS += -lm

APPL_DIRS += \
   $(mkfile_path)test \
   $(mkfile_path)LineTracer \

INCLUDES += \
   -I$(mkfile_path)test \
   -I$(mkfile_path)LineTracer \
	
