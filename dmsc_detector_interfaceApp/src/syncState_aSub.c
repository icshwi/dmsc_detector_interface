#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <stdio.h>
#include <dbDefs.h>
#include <dbFldTypes.h>
#include <dbAccess.h>
#include <link.h>
#include <string.h> // Provides memcpy prototype
#include <stdlib.h> // Provides calloc prototyp


static long syncState_aSub(aSubRecord *prec) {

	float evtCode[4];
	double timestamp[4];
	long clkRstEvt, syncPulEvt;
	long tickDelta;
	long  state;
	
	
	
	
	
	state 		= *(long *)prec->a; 	// the value of the state input record
	clkRstEvt 	= *(long *)prec->b;	// the clock reset event number
	syncPulEvt  = *(long *)prec->c;	// the sync pulse event number
	tickDelta  	= *(long *)prec->d;	// The number of nanoseconds between clk rst and sync
	
	
	
	if(!state){	//initial syncPulEvt
		
		
		
		evtCode[0] = (float) clkRstEvt;
		
		evtCode[1] = (float) syncPulEvt;
		
		
		evtCode[2] = 127;
		
		timestamp[0] = 0;
		
		timestamp[1] = (double) tickDelta;
		
		*(int *)prec->valc = 1; //single
		//Output event list
		prec->neva = 3;	
		memcpy(prec->vala, evtCode, 3 * sizeof(evtCode[0]));
		
		//Output tick list
		prec->nevb = 2;
		memcpy(prec->valb, timestamp, 2 * sizeof(timestamp[0]));
	}
	else{		//check sync state
		
		evtCode[0] = (float) syncPulEvt;
		
		evtCode[1] = 127;
		
		timestamp[0] = 0;
		
		
		*(int *)prec->valc = 0; //normal
		
		//Output event list
		prec->neva = 2;	
		memcpy(prec->vala, evtCode, 2*sizeof(evtCode[0]));
		
		//Output tick list
		prec->nevb = 1;
		memcpy(prec->valb, timestamp, sizeof(timestamp[0]));
	
	}
	
	
	return 0;

}


//register the function with the dbd file

epicsRegisterFunction(syncState_aSub);




