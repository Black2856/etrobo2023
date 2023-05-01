mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS +=

#<mk_files>
APPL_CXXOBJS += \
#</mk_files>

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif

APPL_LIBS += -lm

#<mk_dirs1>
APPL_DIRS += \
#</mk_dirs1>

#<mk_dirs2>
INCLUDES += \
#</mk_dirs2>
