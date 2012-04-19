#include <iostream>

#include "Entity.h"

#include "Object.h"
#include "World.h"

Entity::Entity()
{
  initEntity(0,0,0,"hrk");
}

void Entity::initEntity(int inX, int inY, int inId, std::string inName)
{
  vitals.x = inX;
  vitals.y = inY;
  targetPos.x = inX;
  targetPos.y = inY;
  target = NULL;
  vitals.id = inId;
  vitals.timeAlive = 0;
  vitals.coreTemp = 37;
  vitals.name = inName;

  stats.hunger = 0;
  stats.thirst = 0;
  stats.tired = 0;
  stats.moveSpeed = 50;

  alive = true;
  nightyBye = false;
}

// A function that sets in the course of action based on the decision made by the brain
void Entity::processDecision(e_brainState decision, World* host, s_frameResolution* resPointer)
{
  switch (decision)
    {
    case e_idle:
      break;
    case e_getFood:
      {
	Object* targetObj = 0;
	float closeDist = 100000000000;
	std::vector<Object>::iterator it;
	for (it = host->getObjectList()->begin(); it != host->getObjectList()->end(); ++it)
	  {	    
	    Object tempObj = *it;
	    if (tempObj.pollObject() == Object::e_food)
	      {	      
		float diffX = abs(tempObj.getObjVitals().x - vitals.x);
		float diffY = abs(tempObj.getObjVitals().y - vitals.y);
		float len = sqrt(diffX*diffX+diffY*diffY);
		if (len < closeDist)
		  {
		    closeDist = len;
		    targetObj = &*it;
		  }
	      }

	    if (targetObj)
	      {
		resPointer->resultState = e_eatFood;
		resPointer->target = (void*)targetObj;
	      }
	  }
      }
      break;
    case e_getWater:
      {
	int terSize = host->im_getTerrainMap()->getMapSize();
	int iterCount = 0;
	bool targetPicked = false;
	while (!targetPicked)
	  {
	    for (int i = iterCount*(-1); i <= iterCount; i++)
	      {
		// There's a bug in here with at least one of the getLocationAtCoord params	  
		int y = vitals.y - iterCount;
		y = (y >= 0 ? y : 0);
		int x = vitals.x + i;
		x = (x >= 0 ? x : 0);
		x = (x < terSize ? x : terSize-1);
		creators::e_terrainType terr = host->im_getTerrainMap()->getLocationAtCoord(x,y);
		if (terr == creators::e_shallowWater || terr == creators::e_water)
		  {
		    targetPicked = true;
		    s_position* targPos = new s_position();
		    targPos->x = x;
		    targPos->y = y;
		    resPointer->target = (void*)targPos;
		  }
		y = vitals.y + iterCount;
		y = (y < terSize ? y : terSize-1);
		terr = host->im_getTerrainMap()->getLocationAtCoord(x,y);
		if (terr == creators::e_shallowWater || terr == creators::e_water)
		  {
		    targetPicked = true;
		    s_position* targPos = new s_position();
		    targPos->x = x;
		    targPos->y = y;
		    resPointer->target = (void*)targPos;
		  }
		x = vitals.x - iterCount;
		x = (x >= 0 ? x : 0);
		y = vitals.y + i;
		y = (y >= 0 ? y : 0);
		y = (y < terSize ? y : terSize-1);
		terr = host->im_getTerrainMap()->getLocationAtCoord(x,y);
		if (terr == creators::e_shallowWater || terr == creators::e_water)
		  {
		    targetPicked = true;
		    s_position* targPos = new s_position();
		    targPos->x = x;
		    targPos->y = y;
		    resPointer->target = (void*)targPos;
		  }
		x = vitals.x + iterCount;
		x = (x < terSize ? x : terSize-1);
		terr = host->im_getTerrainMap()->getLocationAtCoord(x,y);
		if (terr == creators::e_shallowWater || terr == creators::e_water)
		  {
		    targetPicked = true;
		    s_position* targPos = new s_position();
		    targPos->x = x;
		    targPos->y = y;
		    resPointer->target = (void*)targPos;
		  }
	      }
	    iterCount++;
	  }
	resPointer->resultState = e_drinkWater;
      }
      break;
    case e_takeNap:
      {
	resPointer->resultState = e_nap;
	resPointer->target = NULL;
      }
      break;
    }
}

void Entity::resolveFrame(s_frameResolution* resultState, World* host)
{
  switch(resultState->resultState)
    {
    case e_eatFood:
      {
	Object* targetFood = (Object*)resultState->target;
	if (vitals.x == targetFood->getObjVitals().x && vitals.y == targetFood->getObjVitals().y)
	  {
	    std::cout << "Eat Da Food at " << targetFood->getObjVitals().x << "," << targetFood->getObjVitals().y << "!!" << std::endl;
	    stats.hunger = 0;
	    host->consumeObject(targetFood);
	  }
	else
	  {
	    moveToTargetLocation(targetFood->getObjVitals().x, targetFood->getObjVitals().y);
	  }
      }
      break;
    case e_drinkWater:
      {
	s_position* waterPos = (s_position*)resultState->target;      
	if (vitals.x == waterPos->x && vitals.y == waterPos->y)
	  {
	    std::cout << "Drink da watah at " << waterPos->x << "," << waterPos->y << "!!" << std::endl;
	    stats.thirst = 0;
	  }
	else
	  {
	    moveToTargetLocation(waterPos->x, waterPos->y);
	  }
      }
      break;
    case e_nap:
      {
	if (!nightyBye)
	  {
	    if (stats.thirst < 70 && stats.hunger < 150)
	      {	      
		std::cout << "Taking a nap" << std::endl;
		nightyBye = true;
	      }
	    else
	      {
		if (stats.thirst > 70)
		  std::cout << "Can't sleep: Too thirsty" << std::endl;
		if (stats.hunger > 150)
		  std::cout << "Can't sleep: Too hungry" << std::endl;
	      }
	  }
	if (nightyBye)
	  {
	    if (stats.thirst > 70)
	      {
		std::cout << "Wakes up: Thirsty" << std::endl;
		nightyBye = false;
	      }
	  }
      }
    default:
      break;
    }
}

void Entity::runFrame(World* host)
{
  // Check to see if the character is alive at all, if not no need to do anything else
  if (alive)
    {
      s_frameResolution state;
      state.resultState = e_idleFrame;
      state.target = 0;
      // Runs the decision making and then processes that decision to select a course of action
      processDecision(smarts.runFrame(this), host, &state);

      // Doing the various vital statistics updating first
      vitals.timeAlive += 1;
      if (vitals.timeAlive % 150 == 0)
	{
	  // The hunger section
	  stats.hunger += 1;
	  if (stats.hunger == 150)
	    {
	      std::cout << "Getting hungry" << std::endl;
	    }
	  else if (stats.hunger == 200)
	    {
	      std::cout << "Getting very hungry" << std::endl;
	    }
	  else if (stats.hunger == 270)
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
	  if (host->im_getWeatherMap()->getLocationAtCoord(vitals.x, vitals.y) != vitals.coreTemp)
	    {
	      vitals.coreTemp = 
		(host->im_getWeatherMap()->getLocationAtCoord(vitals.x, vitals.y) > vitals.coreTemp ? 
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

	  // The sleepy section
	  if (nightyBye)
	    stats.tired -= 10;
	  else
	    stats.tired += 1;
	  if (nightyBye && stats.tired == 0)
	    {
	      std::cout << "Waking up" << std::endl;
	      nightyBye = false;
	    }
	}

      // The movement section
      if (vitals.timeAlive % stats.moveSpeed == 0)
	{
	  if (vitals.x != targetPos.x)
	    vitals.x = (targetPos.x > vitals.x ? vitals.x + 1 : vitals.x - 1);
	  if (vitals.y != targetPos.y)
	    vitals.y = (targetPos.y > vitals.y ? vitals.y + 1 : vitals.y - 1);
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
      if (stats.hunger == 300)
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

      resolveFrame(&state, host);
    }
}

void Entity::moveToTargetLocation(float x, float y)
{
  targetPos.x = x;
  targetPos.y = y;
}

void Entity::moveToTargetLocation(int x, int y)
{
  targetPos.x = x;
  targetPos.y = y;
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
