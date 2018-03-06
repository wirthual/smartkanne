#include "Tea.h"

Tea::Tea(){}
Tea::Tea (String name,int timeSec, int tempC, unsigned long uid) {
  _name = name;
  _timeSec = timeSec;
  _tempC = tempC;
  _uid = uid;
}

String Tea::getName() {
  return _name;
}

int Tea::getTempC() {
  return _tempC;
}

int Tea::getTimeSec() {
  return _timeSec;
}

unsigned long Tea::getUid() {
  return _uid;
}
