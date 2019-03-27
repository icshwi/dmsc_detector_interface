#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <stdio.h>
#include <dbDefs.h>
#include <dbFldTypes.h>
#include <dbAccess.h>
#include <link.h>


static int syncState_aSub(aSubRecord *prec) {

	int i, evtCode*,timestamp*, runMode*,clkRstEvt,syncPulEvt,state,tickDelta;
	
	
	
	
	
	state 		= *(int *)prec->a; 	// the value of the state input record
	clkRstEvt 	= *(int *)prec->b;	// the clock reset event number
	syncPulEvt  = *(int *)prec->c;	// the sync pulse event number
	tickDelta  	= *(int *)prec->d;	// The number of ticks between clk reset and sync trig
	
	evtCode 	= (int *)prec->vala; 	//The output fields which hold the values in outa, the seq array
	timestamp 	= (int *)prec->valb; 	//The output fields which hold the values in outb, the timestamp array
	runMode 	= (int *)prec->valc; 	//the run mode (normal or single)
	if(!state){	//initial syncPulEvt
		evtCode[0] = clkRstEvt;
		evtCode[1] = syncPulEvt;
		
		timestamp[0] = 0;
		timestamp[1] = tickDelta;
		runMode = 1; //single
	}
	else{		//check sync state
		evtCode[0] = syncPulEvt;
		evtCode[1] = 0;
		
		timestamp[0] = 0;
		timestamp[1] = 0;
		
		runMode = 0; //normal
		
	}
	

}


//register the function with the dbd file

epicsRegisterFunction(syncState_aSub);




