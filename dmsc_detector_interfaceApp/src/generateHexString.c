#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <stdio.h>
#include <dbDefs.h>
#include <dbFldTypes.h>
#include <dbAccess.h>
#include <link.h>
#include <string.h>


static int generateHexString(aSubRecord *prec) {
  int CurrentValue = *(int *)prec->a;
  
  epicsOldString* StrOut = (epicsOldString*)prec->vala;
  int BufferSize = 20;
  char StrBuffer[BufferSize];
  int CharsPrinted = snprintf(StrBuffer, BufferSize, "0x%08x", CurrentValue);
  if (CharsPrinted > 0 && CharsPrinted <= BufferSize) {
    memcpy((char*)StrOut, StrBuffer, CharsPrinted + 1);
  } else {
    return -1; //Failure
  }
  return 0;
}


//register the function with the dbd file

epicsRegisterFunction(generateHexString);




