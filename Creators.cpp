#include "Creators.h"

#include <iostream>
#include <math.h>

#define PI 3.14159265

namespace creators
{

  namespace
  {
    double interpolate(double x, double y, double fract)
    {
      double fract_deg = fract * PI;
      double f = (1 - cos(fract_deg)) * .5;

      return x*(1-f)+y*f;
    }

    double smooth(double x, double y, int i, ShiftRand* rando)
    {
      double corners = ((rando->next()+rando->next()+rando->next()+rando->next())/16);
      double sides = ((rando->next()+rando->next()+rando->next()+rando->next())/8);
      double centre = (rando->next()/4);

      return corners+sides+centre;
    }

     double interpNoise(double x, double y, int i, ShiftRand* rando)
    {
      int int_x = int(x);
      double fract_x = x - int_x;

      int int_y = int(y);
      double fract_y = y - int_y;

      double v1 = smooth(int_x, int_y, i, rando);
      double v2 = smooth(int_x + 1, int_y, i, rando);
      double v3 = smooth(int_x, int_y + 1, i, rando);
      double v4 = smooth(int_x + 1, int_y + 1, i, rando);

      double i1 = interpolate(v1, v2, fract_x);
      double i2 = interpolate(v3, v4, fract_x);

      return interpolate(i1, i2, fract_y);
    }

    double perlin(int x, int y, ShiftRand* rando)
    {
      double total = 0;
      double persistence = 0.25;
      double octaves = 9;

      for (int i = 0; i < octaves; i++)
	{
	  double frequency = pow(2, i);
	  double amplitude = pow(persistence, i);

	  total = (total + interpNoise(x*frequency, y*frequency, i, rando) * amplitude);
	}

      return total/octaves;
    }
  }

  bool fillTerrain(Map<double>* terrainMap)
  {
    ShiftRand terrainGen;
    int mapSize = terrainMap->getMapSize();
    int hMin = 1000000000;
    int hMax = 0;
    for (int x = 0; x < mapSize; x++)
      {
	for (int y = 0; y < mapSize; y++)
	  {
	    double hVal = perlin(x,y,&terrainGen);
	    if (hVal > hMax)
	      hMax = hVal;
	    if (hVal < hMin)
	      hMin = hVal;
	    terrainMap->setLocationAtCoord(x,y,hVal);
	  }
      }

    for (int x = 0; x < mapSize; x++)
      {
	for (int y = 0; y < mapSize; y++)
	  {
	    double swap = terrainMap->getLocationAtCoord(x,y);
	    swap = (swap-hMin)/(hMax-hMin);
	    terrainMap->setLocationAtCoord(x,y,swap);
	    std::cout << terrainMap->getLocationAtCoord(x,y) << " ";
	  }
	std::cout << std::endl;
      }
    return true;
  }
}
