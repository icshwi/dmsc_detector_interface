TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = dmsc-detector-interface
# dmsc-detector-interface.dbd will be created and installed
DBD += dmsc-detector-interface.dbd

# dmsc-detector-interface.dbd will be made up from these files:
dmsc-detector-interface_DBD += base.dbd

# Include dbd files from all support applications:
#dmsc-detector-interface_DBD += xxx.dbd

# Add all the support libraries needed by this IOC
#dmsc-detector-interface_LIBS += xxx

# dmsc-detector-interface_registerRecordDeviceDriver.cpp derives from dmsc-detector-interface.dbd
dmsc-detector-interface_SRCS += dmsc-detector-interface_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
dmsc-detector-interface_SRCS_DEFAULT += dmsc-detector-interfaceMain.cpp
dmsc-detector-interface_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#dmsc-detector-interface_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
dmsc-detector-interface_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

