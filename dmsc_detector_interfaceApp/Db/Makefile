TOP=../..
include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE

#----------------------------------------------------
# Create and install (or just install) into <top>/db
# databases, templates, substitutions like this
DB += detector_controls.db
DB += ro_register.db
DB += ro_hex_register.db
DB += ro_2x16bit_register.db
DB += rw_register.db
DB += rw_ip_address.db
DB += rw_mac_address.db
DB += ch_offset.db
DB += reset_register.db
DB += sampling_mode.db
DB += clock_select.db
DB += payload_select.db
DB += oversampling.db
DB += channel_gain.db
DB += softEventCounter.db
DB += timestamp_sync_2.db
DB += timestamp_sync.db
DB += ws_register.db
DB += threshold.db
DB += packetTimeout_register.db
DB += peakDetection_reg.db
DB += buildTime_register.db

#----------------------------------------------------
# If <anyname>.db template is not named <anyname>*.template add
# <anyname>_template = <templatename>

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

