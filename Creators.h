#ifndef _CREATORS_H
#define _CREATORS_H

#include "../../../tools/xorshift.h"

#include "Map.h"
#include "Weather.h"

namespace creators
{

  enum e_terrainType
  {
    e_grass,
    e_water,
    e_mountain,
    e_shallowWater,
    e_hill
  };

  bool fillTerrain(Map<double>* outMap);

  bool fillWeather(Map<int>* weatherMap);

  bool fillTerrainDetails(Map<e_terrainType>* terrainMap, Map<double>* worldMap);
}

#endif //CREATORS_H
