#!../../bin/linux-x86_64/dmsc-detector-interface

#- You may have to change dmsc-detector-interface to something else
#- everywhere it appears in this file

#< envPaths

## Register all support components
dbLoadDatabase("../../dbd/dmsc-detector-interface.dbd",0,0)
dmsc_detector_interface_registerRecordDeviceDriver(pdbbase) 

## Load record instances
dbLoadRecords("../../db/dmsc-detector-interface.db","user=waynelewis")

iocInit()

## Start any sequence programs
#seq sncdmsc-detector-interface,"user=waynelewis"
