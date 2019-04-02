#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <stdio.h>
#include <dbDefs.h>
#include <dbFldTypes.h>
#include <dbAccess.h>
#include <link.h>
#include <math.h>


static int getTimeStamp_aSub(aSubRecord *prec) {

epicsTimeStamp tick;    
unsigned long nSecRem=0;
unsigned long carrySec=0;
unsigned long fracNsecDelta=0; // given in nanoseconds
unsigned long firmware_nanoseconds = 0;
unsigned long firmware_seconds = 0;
unsigned long ICSTICKSPERSECOND = 88052500;
unsigned long FPGATICKSPERSECOND= 44026250;
unsigned long NANOSPERSECOND = 1E9;
	
	if (!dbGetTimeStamp(&prec->inpa, &tick)){ 			
		printf("Initial sec %lu ICS nsec %lu\n",tick.secPastEpoch,tick.nsec);
		
		
		fracNsecDelta = *(long *)prec->b;
		printf("nSec Delta %lu\n",fracNsecDelta);
		
		//Deal with the carry
		nSecRem = (tick.nsec + fracNsecDelta)%NANOSPERSECOND;
		carrySec = floor((tick.nsec + fracNsecDelta)/1E9);
		printf("carrySec  =%lu \n",carrySec);
		//convert nanoseconds into FPGA ticks
		firmware_nanoseconds = floor((nSecRem/1E9)*FPGATICKSPERSECOND);
		firmware_seconds = tick.secPastEpoch + carrySec + 631152000; //Add the time to shift to UNIX time
		
		if(firmware_nanoseconds>=FPGATICKSPERSECOND){
			printf("nanoseconds overflow %lu\n",firmware_nanoseconds);
			return -1; /*Raise SOFT_ALARM, BRSV */
		}
		
		*(unsigned long *)prec->vala = firmware_seconds; 		//Seconds past EPICS TimeStamp Epoch	
		*(unsigned long *)prec->valb = firmware_nanoseconds;	//Fractional Nanoseconds Word		
		
		printf("Resulting sec %lu ICS nsec %lu\n",firmware_seconds,nSecRem);
		printf("Represented as sec %lu firmware ticks %lu\n",firmware_seconds,firmware_nanoseconds);
		return 0; 
	}
	else{
		printf("Could not retrieve timestamp.\n"); 
		return -1; /*Raise SOFT_ALARM, BRSV */
	}

}


//register the function with the dbd file

epicsRegisterFunction(getTimeStamp_aSub);




