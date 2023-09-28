
mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS +=

#<mk_files>
APPL_CXXOBJS += \
    Calc.o \
    Calibration.o \
    DeviceInOut.o \
    GeneralData.o \
    Judge.o \
    JudgeAngle.o \
    JudgeAngleMinifig.o \
    JudgeBrightness.o \
    JudgeButton.o \
    JudgeColor.o \
    JudgeMileage.o \
    JudgeNumerical.o \
    JudgeReturn.o \
    JudgeSonar.o \
    JudgeTime.o \
    JudgeTouch.o \
    LineTrace.o \
    Localization.o \
    Manual.o \
    ManualPID.o \
    PIDControl.o \
    PWMCalc.o \
    RGBtoHSV.o \
    Record.o \
    SensorData.o \
    SpeedCorrection.o \
    Stop.o \
    TakePhoto.o \
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
    $(mkfile_path)spike \
    $(mkfile_path)spike/calc \
    $(mkfile_path)spike/device \
    $(mkfile_path)spike/info \
    $(mkfile_path)spike/judge \
    $(mkfile_path)spike/move \
    $(mkfile_path)spike/recvFile \
    $(mkfile_path)spike/scenario \
#</mk_dirs1>

#<mk_dirs2>
INCLUDES += \
    -I$(mkfile_path)spike \
    -I$(mkfile_path)spike/calc \
    -I$(mkfile_path)spike/device \
    -I$(mkfile_path)spike/info \
    -I$(mkfile_path)spike/judge \
    -I$(mkfile_path)spike/move \
    -I$(mkfile_path)spike/recvFile \
    -I$(mkfile_path)spike/scenario \
#</mk_dirs2>

COPTS += -DMAKE_EV3 -std=c++14 -std=c++1y