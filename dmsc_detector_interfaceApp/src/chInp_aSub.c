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


static long chInp_aSub(aSubRecord *prec) {

	long gnd;
	long impedance;
	long range;	
	
	
	
	
	gnd 		= *(long *)prec->a; 	// the value of the state input record
	impedance 	= *(long *)prec->b;	// the clock reset event number
	range		= *(long *)prec->c;	// the sync pulse event number
	
	
	//	printf("gnd = %d, impedance  =%d, range = %d \n",gnd,impedance, range);

	if(gnd){
		
		*(long *)prec->vala = 64; 
		
	}
	else{		// channel isn't grounded, so set the input impedance

		if(impedance){ 	//1=1K, 0=50 Ohms
			if(range == 0){ //0.05V
				*(long *)prec->vala = 35;
			}
			else if(range == 1){ //0.5V
				*(long *)prec->vala = 17;
			}
			else{		//5V
				*(long *)prec->vala = 69;
			} 

		}
		else{
	   	 	if(range == 0){ //0.05V
                                *(long *)prec->vala = 43;
                        }
                        else if(range == 1){ //0.5V
                                *(long *)prec->vala = 25;
                        }
                        else{           //5V
                                *(long *)prec->vala = 77;
                        }

		}
	}	
	
	return 0;

}


//register the function with the dbd file

epicsRegisterFunction(chInp_aSub);




