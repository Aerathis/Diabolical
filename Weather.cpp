#include "Weather.h"

Weather::Weather()
{
}

void Weather::setWeatherMapSize(int size)
{
  weatherMap.setSize(size);
}

Map<double>* Weather::getWeatherMap()
{
  return &weatherMap;
}

bool Weather::runFrame()
{
}
