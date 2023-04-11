mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS += \
#<mk_files>
#</mk_files>

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif

APPL_LIBS += -lm

APPL_DIRS += \
#<mk_dirs1>
    $(mkfile_path)unit/run \
    $(mkfile_path)unit/judge \
    $(mkfile_path)ê›åv \
    $(mkfile_path)unit/calc \
    $(mkfile_path)unit \
    $(mkfile_path)unit/manage_scenario \
    $(mkfile_path)unit/device \
#</mk_dirs1>

INCLUDES += \
#<mk_dirs2>
    -I$(mkfile_path)unit/device \
    -I$(mkfile_path)unit/judge \
    -I$(mkfile_path)unit/run \
    -I$(mkfile_path)unit \
    -I$(mkfile_path)unit/manage_scenario \
    -I$(mkfile_path)unit/calc \
    -I$(mkfile_path)ê›åv \
#</mk_dirs2>
