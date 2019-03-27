TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = dmsc_detector_interface
# dmsc_detector_interface.dbd will be created and installed
DBD += dmsc_detector_interface.dbd

# dmsc_detector_interface.dbd will be made up from these files:
dmsc_detector_interface_DBD += base.dbd

# Include dbd files from all support applications:
dmsc_detector_interface_DBD += detectorinterface.dbd
dmsc_detector_interface_DBD += convertIPAddress.dbd
dmsc_detector_interface_DBD += convertMACAddress.dbd

# Add all the support libraries needed by this IOC
#dmsc_detector_interface_LIBS += xxx

# dmsc_detector_interface_registerRecordDeviceDriver.cpp derives from dmsc_detector_interface.dbd
dmsc_detector_interface_SRCS += dmsc_detector_interface_registerRecordDeviceDriver.cpp
dmsc_detector_interface_SRCS += convertIPAddress.cpp
dmsc_detector_interface_SRCS += convertMACAddress.cpp
dmsc_detector_interface_SRCS += getTimeStamp_aSub.c
dmsc_detector_interface_SRCS += syncState_aSub.c

# Build the main IOC entry point on workstation OSs.
dmsc_detector_interface_SRCS_DEFAULT += dmsc_detector_interfaceMain.cpp
dmsc_detector_interface_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#dmsc_detector_interface_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
dmsc_detector_interface_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

