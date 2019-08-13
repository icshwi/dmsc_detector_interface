#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <stdio.h>
#include <dbDefs.h>
#include <dbFldTypes.h>
#include <dbAccess.h>
#include <link.h>


static long getRange_aSub(aSubRecord *prec) {

	double range = 0;
	long  state;
		
	state 		= *(long *)prec->a; 	// the value of the state input record
	
	//printf("State = %lu ",state);
	
	if(state == 0 || state == 3){ 	// +/-5V 
		range = 5.0*2;
	}
	else if(state == 1 || state == 4){// +/-0.5V 
		range = 0.5*2;
	}
	else if(state == 2 || state == 5){// +/-50mV 
		range = 0.05*2;
	}
	else {
		range = 0;
	}
	//printf("Range = %f\n",range);
	*(double *)prec->vala = range; //single
		
	
	return 0;

}


//register the function with the dbd file

epicsRegisterFunction(getRange_aSub);




