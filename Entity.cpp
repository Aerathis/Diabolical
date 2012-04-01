#include <iostream>

#include "Entity.h"

Entity::Entity()
{
}

void Entity::initEntity(int inX, int inY, int inId, std::string inName)
{
  vitals.x = inX;
  vitals.y = inY;
  targetX = inX;
  targetY = inY;
  vitals.id = inId;
  vitals.timeAlive = 0;
  vitals.coreTemp = 37;
  vitals.name = inName;

  stats.hunger = 0;
  stats.thirst = 0;
  stats.tired = 0;
  stats.moveSpeed = 500;
}

void Entity::runFrame()
{
  vitals.timeAlive += 1;
  if (vitals.timeAlive % 1500 == 0)
    {
      stats.hunger += 1;
      stats.thirst += 1;
    }
  if (vitals.timeAlive % stats.moveSpeed == 0)
    {
      if (vitals.x != targetX)
	vitals.x = (targetX > vitals.x ? vitals.x + 1 : vitals.x - 1);
      if (vitals.y != targetY)
	vitals.y = (targetY > vitals.y ? vitals.y + 1 : vitals.y - 1);
    }
  if (target != NULL)
    {
      if (vitals.x != target->getVitals().x && vitals.y != target->getVitals().y)
	{
	  moveToTargetLocation(target->getVitals().x, target->getVitals().y);
	}
      else
	{
	  std::cout << "Target Entity Reached" << std::endl;
	  target = NULL;
	}
    }
}

void Entity::moveToTargetLocation(int x, int y)
{
  targetX = x;
  targetY = y;
}

void Entity::moveToTarget(Entity* targ)
{
  target = targ;
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
