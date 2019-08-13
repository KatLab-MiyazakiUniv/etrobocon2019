mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_CXXOBJS += \
    Controller.o \
    Display.o \
    EtRobocon2019.o \
    Filter.o \
    Distance.o \
    Calibrator.o \
    Pid.o \
    LineTracer.o \
    SpeedControl.o \
    TurnControl.o \
    NormalCourse.o \
    Navigator.o \
    Logger.o \
    Rotation.o \
    BlockBingo.o

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif

APPL_DIR += \
    $(mkfile_path)/module \
    $(mkfile_path)/module/api \
    $(mkfile_path)/module/api/core

INCLUDES += \
    -I$(mkfile_path)/module \
    -I$(mkfile_path)/module/api \
    -I$(mkfile_path)/module/api/core

# COPTS += -fno-use-cxa-atexit
