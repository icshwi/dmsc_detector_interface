This support module implements a protocol to communicate between an IOC running on a host server and a detector readout master. It defines parameter template files which instantiate records required for a particular parameter. 

# Using this support module

This support module has a dependency on [Stream Device](https://paulscherrerinstitute.github.io/StreamDevice/) and [Autosave](http://htmlpreview.github.io/?https://github.com/epics-modules/autosave/blob/R5-7-1/documentation/autoSaveRestore.html).

In the st.cmd file you will need to specify where the protocol file is to be found. You will also need to set up the Stream Device port. 

```
epicsEnvSet("STREAM_PROTOCOL_PATH","/epics/base-7.0.3.1/require/3.1.2/siteApps/dmsc_detector_interface/master/db")
epicsEnvSet("PROTO", "ics-dg-udp.proto")

epicsEnvSet("DestIP", "192.168.10.2")
epicsEnvSet("DestPort", "65535")
epicsEnvSet("SrcPort", "65534")
drvAsynIPPortConfigure ("UDP","$(DestIP):$(DestPort):$(SrcPort) UDP")

```

The support module is intended to be used with the [parameter generation script](https://github.com/icshwi/det_param_gen). This creates cmd files with macros populated according to a parameter description. The cmd files can then be loaded into the IOC with somthing like

```
iocshLoad("$(MASTER)/$(OUTPUT)/ctl_params_mst.cmd", "DEV=$(DEV), COM=UDP, SYS=$(SYS), PROTO=$(PROTO)")
```

# Protocol Implementation

The protocol is implemented using [stream device](https://paulscherrerinstitute.github.io/StreamDevice/). A protocol file (protocol/ics-dg-udp.proto) defines how to read and write to 1,2, or 3 registers. Offsets to different registers are defined by macros. In this way a single protocol can be used by lots of different records with different register offsets. For more details on implementation see the comments in the protocol file and refer to the documentation on the stream device website. 

# Parameter Types

Parameter template files use macros to specify the offset of the register(s) they relate to. Other macros can be defined to modify behaviour at startup, to add limits and alarms, and to change the names of the records generated. The template files themselves document what each macro does. 

| Parameter Type | Template File | aSub Records | Descripton |
| :-- | :-- | :-- | :-- |
| Read Write | rw_register.db | na | Writes to a 32 bit register. Reads that register back into a record |
| Read Only | ro_register.db | na | Reads a 32 bit register into a record |
| Git Hash | githash_register.db | printGitHash_aSub.c | Reads 3 32 bit registers and parses them to form a githash hex string |
| Build Time | buildTime_register.db | getTimeStamp_aSub.c | Reads a 32 bit register and parses it to determine the firmware build time |
| MAC | rw_mac_address.db | convertMACAddress.cpp | Parses a MAC string record and populates 2 32 bit registers. Reads back those registers and populates a MAC string |
| IP | rw_ip_address.db | convertIPAddress.cpp | Parses an IP address string record and populates a 32 bit register. Reads back the register and populates a IP address string |
| Reset | reset_register.db | na | Sends a reset or enable command to the readout master |


