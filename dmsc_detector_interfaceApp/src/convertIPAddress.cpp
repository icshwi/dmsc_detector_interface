#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <stdio.h>
#include <dbDefs.h>
#include <dbFldTypes.h>
#include <dbAccess.h>
#include <link.h>
#include <string.h>

#include <string>
#include <vector>
#include <exception>

static int ipStringToInt(std::string Input) {
  std::stringstream ss;
  ss.str(Input);
  std::vector<int> Parts;
  int Temp;
  while (not ss.eof()) {
    ss >> Temp;
    if (Temp < 0 or Temp > 255 or ss.fail()) {
      throw std::runtime_error("Unable to extract IP address.");
    }
    Parts.push_back(Temp);
    if (ss.eof()) {
      break;
    }
    ss.seekg(1, std::ios::cur);
  }
  if (Parts.size() != 4) {
    throw std::runtime_error("Invalid IP address.");
  }
  int RetValue = 0;
  for (size_t i = 0; i < Parts.size(); i++) {
    RetValue = RetValue << 8;
    RetValue += (Parts[i] & 0xFF);
  }
  return RetValue;
}

extern "C" {
  
static int ipAddrToString(aSubRecord *prec) {
  int CurrentValue = *(int *)prec->a;
  unsigned char Part4 = CurrentValue & 0xFF;
  CurrentValue = CurrentValue >> 8;
  unsigned char Part3 = CurrentValue & 0xFF;
  CurrentValue = CurrentValue >> 8;
  unsigned char Part2 = CurrentValue & 0xFF;
  CurrentValue = CurrentValue >> 8;
  unsigned char Part1 = CurrentValue & 0xFF;
  
  epicsOldString* StrOut = (epicsOldString*)prec->vala;
  int BufferSize = 20;
  char StrBuffer[BufferSize];
  int CharsPrinted = snprintf(StrBuffer, BufferSize, "%u.%u.%u.%u", Part1, Part2, Part3, Part4);
  if (CharsPrinted > 0 && CharsPrinted <= BufferSize) {
    memcpy((char*)StrOut, StrBuffer, CharsPrinted + 1);
  } else {
    return 1; //Failure
  }
  return 0;
}

static int stringToIpAddr(aSubRecord *prec) {
  epicsOldString* StrIn = (epicsOldString*)prec->a;
  std::string IpStr((char*)StrIn);
  
  try {
    int Temp = ipStringToInt(IpStr);
    *(int *)prec->vala = Temp;
  } catch (std::exception &E) {
    return 1;
  }
  return 0;
}
}

//register the function with the dbd file

epicsRegisterFunction(ipAddrToString);
epicsRegisterFunction(stringToIpAddr);




