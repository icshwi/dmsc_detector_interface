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
#include <regex>

#include <string>
#include <regex>
#include <vector>
#include <exception>

static std::pair<int, int> macToInt(std::string Input) {
  unsigned int Upper, Lower;
  int NrOfColons = 0;
  size_t ColonPos = 0;
  while ((ColonPos = Input.find(':')) != std::string::npos) {
    Input.replace(ColonPos, 1, "");
    ++NrOfColons;
  }
  if (NrOfColons != 5 or Input.size() != 12) {
    throw std::runtime_error("Not a valid MAC address.");
  }
  
  std::stringstream ss;
  ss << std::hex << Input.substr(0, 4);
  ss >> Upper;
  if (not ss.eof() or ss.fail()) {
    throw std::runtime_error("Invalid characters in address.");
  }
  ss.str("");
  ss.clear();
  ss << std::hex << Input.substr(4, std::string::npos);
  ss >> Lower;
  if (not ss.eof() or ss.fail()) {
    throw std::runtime_error("Invalid characters in address.");
  }
  return {static_cast<int>(Upper), static_cast<int>(Lower)};
}

static std::string intToMac(int UpperBytes, int LowerBytes) {
  unsigned char Part5 = UpperBytes & 0xFF;
  UpperBytes = UpperBytes >> 8;
  unsigned char Part6 = UpperBytes & 0xFF;

  unsigned char Part1 = LowerBytes & 0xFF;
  LowerBytes = LowerBytes >> 8;
  unsigned char Part2 = LowerBytes & 0xFF;
  LowerBytes = LowerBytes >> 8;
  unsigned char Part3 = LowerBytes & 0xFF;
  LowerBytes = LowerBytes >> 8;
  unsigned char Part4 = LowerBytes & 0xFF;

  int BufferSize = 30;
  char StrBuffer[BufferSize];
  int CharsPrinted = snprintf(StrBuffer, BufferSize, "%02x:%02x:%02x:%02x:%02x:%02x", Part6, Part5, Part4, Part3, Part2, Part1);
  if (CharsPrinted > 0 && CharsPrinted <= BufferSize) {
    return std::string(StrBuffer);
  }
  return ""; //Failure
}


extern "C" {
  
static int macAddrToString(aSubRecord *prec) {
  int UpperBytes = *(int *)prec->a;
  int LowerBytes = *(int *)prec->b;
  
  std::string MacStr = intToMac(UpperBytes, LowerBytes);
  
  if (!MacStr.empty()) {
    epicsOldString* StrOut = (epicsOldString*)prec->vala;
    memcpy((char*)StrOut, MacStr.c_str(), MacStr.size() + 1);
  } else {
    return 1; //Failure
  }
  return 0;
}

static int stringToMacAddr(aSubRecord *prec) {
  epicsOldString* StrIn = (epicsOldString*)prec->a;
  std::string IpStr((char*)StrIn);
  
  try {
    std::pair<int, int> Temp = macToInt(IpStr);
    *(int *)prec->vala = Temp.first;
    *(int *)prec->valb = Temp.second;
  } catch (std::exception &E) {
    return 1;
  }
  return 0;
}
}

//register the function with the dbd file

epicsRegisterFunction(macAddrToString);
epicsRegisterFunction(stringToMacAddr);




