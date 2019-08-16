#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <stdio.h>
#include <dbDefs.h>
#include <dbFldTypes.h>
#include <dbAccess.h>
#include <link.h>
#include <string.h>



static long getBuildTime_aSub(aSubRecord *prec) {

	epicsOldString *outStr;
	long  buildTime;
	int sec;
	int min;
	int hour;
	int year; //counts from year 2000
	int month;
	int day;
		
	buildTime 		= *(long *)prec->a; 	// the value of the state input record
	outStr = (epicsOldString*)prec->vala;
	
	day 	=  buildTime >> 27;
	month 	= (buildTime >> 23) & 0xF;
	year 	= (buildTime >> 17) & 0x3F;
	hour 	= (buildTime >> 12) & 0x1F;
	min 	= (buildTime >> 6) 	& 0x3F;
	sec 	=  buildTime 		& 0x3F;
	
	snprintf(outStr,31,"%.2d/%.2d/%.2d %.2d:%.2d:%.2d",day,month,year,hour,min,sec);
	
	printf("The Firmware Build Time is: ");
	printf(outStr);
	printf("\n");
	
	
	
    //memcpy((char*)outStr, MacStr.c_str(), 32);
		
	
	return 0;

}


//register the function with the dbd file

epicsRegisterFunction(getBuildTime_aSub);




