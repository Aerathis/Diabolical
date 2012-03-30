#ifndef _CREATORS_H
#define _CREATORS_H

#include "../../../tools/xorshift.h"

#include "Map.h"
#include "Weather.h"

namespace creators
{
  bool fillTerrain(Map<double>* outMap);

  bool fillWeather(Map<int>* weatherMap);
}

#endif //CREATORS_H
