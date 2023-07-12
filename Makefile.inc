
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
    state_transition.o \
#</mk_files>

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif

APPL_LIBS += -lm

#<mk_dirs1>
APPL_DIRS += \
    $(mkfile_path)PC \
    $(mkfile_path)PC/manage_signal \
    $(mkfile_path)PC/manage_train \
    $(mkfile_path)PC/recognize_image \
    $(mkfile_path)PC/search_route \
    $(mkfile_path)spike \
    $(mkfile_path)spike/calc \
    $(mkfile_path)spike/device \
    $(mkfile_path)spike/judge \
    $(mkfile_path)spike/move \
    $(mkfile_path)spike/scenario \
    $(mkfile_path)util \
    $(mkfile_path)util/compile \
    $(mkfile_path)util/fix \
    $(mkfile_path)util/scenario \
#</mk_dirs1>

#<mk_dirs2>
INCLUDES += \
    -I$(mkfile_path)PC \
    -I$(mkfile_path)PC/manage_signal \
    -I$(mkfile_path)PC/manage_train \
    -I$(mkfile_path)PC/recognize_image \
    -I$(mkfile_path)PC/search_route \
    -I$(mkfile_path)spike \
    -I$(mkfile_path)spike/calc \
    -I$(mkfile_path)spike/device \
    -I$(mkfile_path)spike/judge \
    -I$(mkfile_path)spike/move \
    -I$(mkfile_path)spike/scenario \
    -I$(mkfile_path)util \
    -I$(mkfile_path)util/compile \
    -I$(mkfile_path)util/fix \
    -I$(mkfile_path)util/scenario \
#</mk_dirs2>

COPTS += -DMAKE_EV3 -std=c++14 -std=c++1y