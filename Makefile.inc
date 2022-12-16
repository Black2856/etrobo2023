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
#</mk_dirs1>

INCLUDES += \
#<mk_dirs2>
#</mk_dirs2>
