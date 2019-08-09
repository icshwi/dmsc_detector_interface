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
unsigned long tickDelta=0; // given in ticks
unsigned long firmware_ticks = 0;
unsigned long firmware_seconds = 0;
unsigned long ICSTICKSPERSECOND = 88052500;
unsigned long NANOSPERSECOND = 1000000000;
double NANOSPERTICK;
double ticksD;
unsigned long ticksC; 
	if (!dbGetTimeStamp(&prec->inpa, &tick)){ 			
				
		//printf("Initial sec %lu ICS nsec %lu ",tick.secPastEpoch,tick.nsec);
		
		NANOSPERTICK = ((double)NANOSPERSECOND/(double)ICSTICKSPERSECOND);
		//printf("NANOSPERTICK = %f ",NANOSPERTICK);
		
		tickDelta = *(long *)prec->b; //in ticks
		//printf("tickDelta = %lu ",tickDelta);
				
		//convert the tick.nsec from nsecs to ticks
		ticksD = tick.nsec/NANOSPERTICK;
		//printf("ticksD = %f ",ticksD);
		
		ticksC = floor(ticksD);
		//printf("ticksC = %lu ",ticksC);
		
		//Deal with the carry
		nSecRem = (ticksC + tickDelta)%ICSTICKSPERSECOND; 
		//printf("ticksC + ticksDelta = %lu ",ticksC + tickDelta);
		//printf("nSecRem = %lu ",nSecRem);
		
		
		carrySec = floor((ticksC + tickDelta)/ICSTICKSPERSECOND);
	 	//printf("CarrySec = %lu\n",carrySec); 
		
		//convert ICS ticks into FPGA ticks
		firmware_ticks = floor((nSecRem/2)); //to account for the prescaler clock output
		firmware_seconds = tick.secPastEpoch + carrySec + 631152000; //Add the time to shift to UNIX time
		
		
		*(unsigned long *)prec->vala = firmware_seconds; 		//Seconds past EPICS TimeStamp Epoch	
		*(unsigned long *)prec->valb = firmware_ticks;			//Fractional Nanoseconds Word		
		
		return 0; 
	}
	else{
		printf("Could not retrieve timestamp.\n"); 
		return -1; /*Raise SOFT_ALARM, BRSV */
	}

}


//register the function with the dbd file

epicsRegisterFunction(getTimeStamp_aSub);




