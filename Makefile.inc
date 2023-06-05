mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS +=

#<mk_files>
APPL_CXXOBJS += \
    DeviceInOut.o \
    JudgeAngle.o \
    JudgeMileage.o \
    JudgeNumerical.o \
    JudgeSonar.o \
    JudgeTime.o \
    Localization.o \
    RGBtoHSV.o \
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
    $(mkfile_path)unit/manage_scenario \
    $(mkfile_path)unit/move \
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
    -I$(mkfile_path)unit/manage_scenario \
    -I$(mkfile_path)unit/move \
#</mk_dirs2>
