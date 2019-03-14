TOP=../..
include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE

#----------------------------------------------------
# Create and install (or just install) into <top>/db
# databases, templates, substitutions like this
DB += detector_controls.db
DB += ro_register.db
DB += ro_2x16bit_register.db
DB += rw_register.db
DB += rw_ip_address.db
DB += rw_mac_address.db
DB += reset_register.db
DB += softEventCounter.db
DB += timestamp_sync_2.db
DB += timestamp_sync.db

#----------------------------------------------------
# If <anyname>.db template is not named <anyname>*.template add
# <anyname>_template = <templatename>

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

