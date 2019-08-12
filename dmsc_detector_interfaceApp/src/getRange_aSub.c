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
	unsigned long  state;
		
	state 		= *(unsigned long *)prec->a; 	// the value of the state input record
	
	if(state == 69 || state == 77){ 	// +/-5V 
		range = 5.0*2;
	}
	else if(state == 17 || state == 25){// +/-0.5V 
		range = 0.5*2;
	}
	else if(state == 35 || state == 43){// +/-50mV 
		range = 0.05*2;
	}
	else{
		range = 0;
	}
	*(double *)prec->vala = range; //single
		
	
	return 0;

}


//register the function with the dbd file

epicsRegisterFunction(getRange_aSub);




