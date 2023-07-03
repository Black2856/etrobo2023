
mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS +=

#<mk_files>
APPL_CXXOBJS += \
    Calc.o \
    DeviceInOut.o \
    Judge.o \
    JudgeAngle.o \
    JudgeMileage.o \
    JudgeNumerical.o \
    JudgeSonar.o \
    JudgeTime.o \
    LineTrace.o \
    Localization.o \
    PIDControl.o \
    RGBtoHSV.o \
    SpeedCorrection.o \
    arg_info.o \
    manage_scenario.o \
    manage_scene.o \
    scene.o \
#</mk_files>

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif

APPL_LIBS += -lm

#<mk_dirs1>
APPL_DIRS += \
    $(mkfile_path)app \
    $(mkfile_path)app/manage_signal \
    $(mkfile_path)app/manage_train \
    $(mkfile_path)app/recognize_image \
    $(mkfile_path)app/search_route \
    $(mkfile_path)unit \
    $(mkfile_path)unit/calc \
    $(mkfile_path)unit/device \
    $(mkfile_path)unit/judge \
    $(mkfile_path)unit/move \
    $(mkfile_path)unit/scenario \
#</mk_dirs1>

#<mk_dirs2>
INCLUDES += \
    -I$(mkfile_path)app \
    -I$(mkfile_path)app/manage_signal \
    -I$(mkfile_path)app/manage_train \
    -I$(mkfile_path)app/recognize_image \
    -I$(mkfile_path)app/search_route \
    -I$(mkfile_path)unit \
    -I$(mkfile_path)unit/calc \
    -I$(mkfile_path)unit/device \
    -I$(mkfile_path)unit/judge \
    -I$(mkfile_path)unit/move \
    -I$(mkfile_path)unit/scenario \
#</mk_dirs2>

CXXFLAGS = -O3 -o prog -rdynamic -D_GNU_SOURCE -fno-threadsafe-statics
#COPTS += -DMAKE_EV3 -std=c++14 -std=c++1y