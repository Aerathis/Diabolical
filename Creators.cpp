#include "Creators.h"

bool creators::fillTerrain(Map<int> terrainMap)
{
  ShiftRand terrainGen;
  int mapSize = terrainMap.getMapSize();
  terrainMap.setLocationAtCoord(0,0,1);
  terrainMap.setLocationAtCoord(0,1,1);
  terrainMap.setLocationAtCoord(0,2,1);
  terrainMap.setLocationAtCoord(0,3,1);
  terrainMap.setLocationAtCoord(0,4,1);
  return true;
}
