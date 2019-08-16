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

	char  outStr[32];
	long  buildTime;
	int sec;
	int min;
	int hour;
	int year; //counts from year 2000
	int month;
	int day;
		
	buildTime 		= *(long *)prec->a; 	// the value of the state input record
	
	day 	=  buildTime >> 26;
	month 	= (buildTime >> 21) & 0xF;
	year 	= (buildTime >> 16) & 0x3F;
	hour 	= (buildTime >> 11) & 0x1F;
	min 	= (buildTime >> 6) 	& 0x3F;
	sec 	=  buildTime 		& 0x3F;
	
	snprintf(outStr,32,"%d/%d/%d %d:%d:d",day,month,year,hour,min,sec);
	printf(outStr);
	
	//printf("Range = %f\n",range);
	*(char)prec->vala = range; //single
		
	
	return 0;

}


//register the function with the dbd file

epicsRegisterFunction(getBuildTime_aSub);




