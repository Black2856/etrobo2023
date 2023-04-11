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
    $(mkfile_path)unit/run \
#</mk_dirs1>

INCLUDES += \
#<mk_dirs2>
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
    -I$(mkfile_path)unit/run \
#</mk_dirs2>
