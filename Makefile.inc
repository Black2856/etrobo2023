mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS +=\

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif

APPL_LIBS += -lm

APPL_DIRS += \

INCLUDES += \
