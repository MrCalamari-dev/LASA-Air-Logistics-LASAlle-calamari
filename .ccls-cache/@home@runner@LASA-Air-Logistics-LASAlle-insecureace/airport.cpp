#include "slist.h"
#include <string.h>

Airport::Airport(){
  strcpy(code," ");
  longitude = 0;
  latitude = 0;
}
Airport::Airport(char c[5], double lon, double lat){
  strcpy(code,c);
  longitude = lon;
  latitude = lat;
}
Airport::~Airport(){

}

