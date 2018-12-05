#!/usr/bin/bash

#------- Event Code Sequence Set Up -------------------

caput HZB-V20:TS-EVR-02:SoftSeq0-Disable-Cmd 1
caput HZB-V20:TS-EVR-02:SoftSeq1-Disable-Cmd 1
#sleep 1

caput HZB-V20:TS-EVR-02:SoftSeq0-Unload-Cmd 1
caput HZB-V20:TS-EVR-02:SoftSeq0-Load-Cmd 1

caput HZB-V20:TS-EVR-02:SoftSeq0-TsResolution-Sel  "3"
caget HZB-V20:TS-EVR-02:SoftSeq0-TsResolution-RB

caput HZB-V20:TS-EVR-02:SoftSeq0-TrigSrc-Scale-Sel "Software"
caget HZB-V20:TS-EVR-02:SoftSeq0-TrigSrc-RB

caput HZB-V20:TS-EVR-02:SoftSeq0-RunMode-Sel "Normal"
caget HZB-V20:TS-EVR-02:SoftSeq0-RunMode-RB

caput HZB-V20:TS-EVR-02:SoftSeq0-Enable-Cmd 1



#Define the delays between event codes
caput -a HZB-V20:TS-EVR-02:SoftSeq0-EvtCode-SP    2 15 16

#sleep 1

caget HZB-V20:TS-EVR-02:SoftSeq0-EvtCode-RB

caput -a HZB-V20:TS-EVR-02:SoftSeq0-Timestamp-SP  2 0 1000000000

#sleep 1

caget HZB-V20:TS-EVR-02:SoftSeq0-Timestamp-RB

#caput -a HZB-V20:TS-EVR-02:SoftSeq0-EvtMask-SP    3 0 0 0
#caget HZB-V20:TS-EVR-02:SoftSeq0-EvtMask-RB

caput HZB-V20:TS-EVR-02:SoftSeq0-Commit-Cmd 1

#sleep 1



#sleep 1
#start the sequence (defined above)
caput HZB-V20:TS-EVR-02:SoftSeq0-SoftTrig-Cmd 1
