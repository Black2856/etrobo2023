mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS +=\
   LineTracer.o \
   test.o \
   app.o \

APPL_LIBS += -lm

APPL_DIRS += \
   $(mkfile_path)test \
   $(mkfile_path)LineTracer \
   $(mkfile_path)test/file001 \

INCLUDES += \
   -I$(mkfile_path)LineTracer \
   -I$(mkfile_path)test/file001 \
   -I$(mkfile_path)test \
	
