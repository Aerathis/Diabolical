#ifndef _WEATHER_H
#define _WEATHER_H

#include "Map.h"

class Weather
{
 public:
  Weather();

  void setWeatherMapSize(int size);
  bool runFrame();

  Map<double>* getWeatherMap();
  
 private:
  Map<double> weatherMap;
};

#endif //WEATHER_H
