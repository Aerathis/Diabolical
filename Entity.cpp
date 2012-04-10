#include <iostream>

#include "Entity.h"

class World;

Entity::Entity()
{
  initEntity(0,0,0,"hrk");
}

void Entity::initEntity(int inX, int inY, int inId, std::string inName)
{
  vitals.x = inX;
  vitals.y = inY;
  targetX = inX;
  targetY = inY;
  target = NULL;
  vitals.id = inId;
  vitals.timeAlive = 0;
  vitals.coreTemp = 37;
  vitals.name = inName;

  stats.hunger = 0;
  stats.thirst = 0;
  stats.tired = 0;
  stats.moveSpeed = 500;

  alive = true;
}

void Entity::runFrame(Map<double>* world, Map<int>* weather)
{
  // Check to see if the character is alive at all, if not no need to do anything else
  if (alive)
    {
      decision = smarts.runFrame(this);
      // Doing the various vital statistics updating first
      vitals.timeAlive += 1;
      if (vitals.timeAlive % 1500 == 0)
	{
	  // The hunger section
	  stats.hunger += 1;
	  if (stats.hunger == 50)
	    {
	      std::cout << "Getting hungry" << std::endl;
	    }
	  else if (stats.hunger == 75)
	    {
	      std::cout << "Getting very hungry" << std::endl;
	    }
	  else if (stats.hunger == 93)
	    {
	      std::cout << "Starving!!" << std::endl;
	    }

	  // The thirsty section
	  stats.thirst += 1;
	  if (stats.thirst == 75)
	    {
	      std::cout << "Is extremely thirsty" << std::endl;
	    }
	  if (stats.thirst == 93)
	    {
	      std::cout << "Is dying of thirst" << std::endl;
	    }

	  // The hot/cold section
	  if (weather->getLocationAtCoord(vitals.x, vitals.y) != vitals.coreTemp)
	    {
	      vitals.coreTemp = 
		(weather->getLocationAtCoord(vitals.x, vitals.y) > vitals.coreTemp ? 
		 vitals.coreTemp + 1 : vitals.coreTemp - 1);
	    }
	  if (vitals.coreTemp == 35)
	    {
	      std::cout << "Is feeling cold" << std::endl;
	    }
	  else if (vitals.coreTemp == 32)
	    {
	      std::cout << "Is shivering" << std::endl;
	    }
	  else if (vitals.coreTemp == 28)
	    {
	      std::cout << "Is freezing!!" << std::endl;
	    }
	  if (vitals.coreTemp == 39)
	    {
	      std::cout << "Is feeling warm" << std::endl;
	    }
	  else if (vitals.coreTemp == 42)
	    {
	      std::cout << "Is burning up" << std::endl;
	    }
	}

      // The movement section
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

      // Check to see for any adverse effects based on the current situation
      if (stats.hunger == 100)
	{
	  std::cout << "Has starved to death" << std::endl;
	  alive = false;
	}
      if (stats.thirst == 100)
	{
	  std::cout << "Has died of dehydration" << std::endl;
	  alive = false;
	}
      if (vitals.coreTemp == 20)
	{
	  std::cout << "Has frozen to death" << std::endl;
	  alive = false;
	}
      if (vitals.coreTemp == 46)
	{
	  std::cout << "Has died from the heat" << std::endl;
	  alive = false;
	}
      if (vitals.timeAlive == 10000000)
	{
	  std::cout << "Has passed away of old age" << std::endl;
	  alive = false;
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
