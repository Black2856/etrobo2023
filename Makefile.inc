mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS +=\
   run.o \
   pid.o \
   settings.o \
   measurement_core.o \
   run_area.o \
   vector.o \
   color.o \
   control.o \
   dataIO.o \
   curve.o \
   sectionList.o \
   section.o \
   calibration.o \
   ev3f.o \
   section_core.o \

APPL_LIBS += -lm

APPL_DIRS += \
   $(mkfile_path)measurement \
   $(mkfile_path)control \
   $(mkfile_path)section \

INCLUDES += \
   -I$(mkfile_path)control \
   -I$(mkfile_path)section \
   -I$(mkfile_path)measurement \
	
