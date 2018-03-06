#ifndef TEA_H
#define TEA_H

#include <WString.h>

class Tea
{
  String _name;
  int _timeSec;
  int _tempC;
  long _uid;

public:
  Tea();
  Tea(String name,int timeSec,int tempC,unsigned long uid);
  String getName();
  int getTempC();
  int getTimeSec();
  unsigned long getUid();
};

#endif
