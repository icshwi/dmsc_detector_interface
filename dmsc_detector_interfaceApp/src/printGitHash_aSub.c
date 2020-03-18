#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <stdio.h>
#include <dbDefs.h>
#include <dbFldTypes.h>
#include <dbAccess.h>
#include <link.h>
#include <string.h>


static long printGitHash_aSub(aSubRecord *prec) {

	
	long  lw,mw,uw;
    epicsOldString *outStr;
	
    outStr = (epicsOldString*)prec->vala;

	
	lw 		= *(long *)prec->a; 	// the value of the state input record
    mw 		= *(long *)prec->b; 	// the value of the state input record
    uw 		= *(long *)prec->c; 	// the value of the state input record
	
	snprintf(outStr,28,"%#010X %08X %08X",uw,mw,lw);
		
    printf("The Firmware Git Hash is: ");
	printf(outStr);
	printf("\n");
		
	
	return 0;

}


//register the function with the dbd file

epicsRegisterFunction(printGitHash_aSub);




