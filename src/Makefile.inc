mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_CXXOBJS += \
    Controller.o \
    Display.o \
    EtRobocon2019.o

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif

APPL_DIR += \
    $(mkfile_path)api \
    $(mkfile_path)procedure

INCLUDES += \
    -I$(mkfile_path)api \
    -I$(mkfile_path)procedure

# COPTS += -fno-use-cxa-atexit
