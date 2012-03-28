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
  vitals.name = inName;

  stats.hunger = 0;
  stats.thirst = 0;
  stats.tired = 0;
}

Entity::s_vitals Entity::getVitals()
{
  return vitals;
}

Entity::s_stats Entity::getStats()
{
  return stats;
}
