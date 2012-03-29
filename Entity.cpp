#include <iostream>

#include "Entity.h"

Entity::Entity()
{
}

void Entity::initEntity(int inX, int inY, int inId, std::string inName)
{
  vitals.x = (float)inX;
  vitals.y = (float)inY;
  vitals.id = inId;
  vitals.timeAlive = 0;
  vitals.coreTemp = 37;
  vitals.name = inName;

  stats.hunger = 0;
  stats.thirst = 0;
  stats.tired = 0;
}

void Entity::runFrame()
{
  vitals.timeAlive += 1;
  if (vitals.timeAlive % 1500 == 0)
    {
      stats.hunger += 1;
      stats.thirst += 1;
    }
}

Entity::s_vitals Entity::getVitals()
{
  return vitals;
}

Entity::s_stats Entity::getStats()
{
  return stats;
}

void Entity::testLocChange(int newX)
{
  vitals.x = newX;
}
