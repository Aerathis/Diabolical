#include "Structure.h"

#include <iostream>

Structure::Structure() : Object(Object::e_structure)
{
  structType = e_home;
  completionPercent = 0;
  constructionTimeScale = 1;
  completed = false;
  underConstruction = false;
  needMats = false;
  ownable = true;
  owner = NULL;
  materialReqs[e_wood] = 10;
  materialReqs[e_stone] = 1;
  totalMats = materialReqs[e_wood] + materialReqs[e_stone];
  //materialsPresent[e_wood] = 0;
  //materialsPresent[e_stone] = 0;
  // Total debugging hack make sure to remove when testing is complete
  materialsPresent[e_stone] = 1;
  materialsPresent[e_wood] = 0;
}

void Structure::runFrame()
{
  if (underConstruction)
    {
      completionPercent += 1 * constructionTimeScale;
      int currentOutMats = materialReqs[e_wood] + materialReqs[e_stone];
      int remainScale = totalMats - currentOutMats;
      int perc = int((float)COMPLETE/(float)totalMats);      
      if (completionPercent >= (perc * remainScale))
	{
	  if (materialsPresent[e_wood] == 0 && materialsPresent[e_stone] == 0)
	    {
	      std::cout << "Construction Paused: Need materials" << std::endl;
	      underConstruction = false;
	      needMats = true;
	    }
	  else
	    {
	      bool needWood = (materialReqs[e_wood] > 0 ? true : false);
	      bool hasWood = (materialsPresent[e_wood] > 0 ? true : false);
	      bool needStone = (materialReqs[e_stone] > 0 ? true : false);
	      bool hasStone = (materialsPresent[e_stone] > 0 ? true : false);
	      if (needWood && needStone)
		{
		  
		}
	      else if (needWood && !needStone)
		{
		}
	      else if (needStone && !needWood)
		{
		}
	    }
	}
      if (completionPercent >= COMPLETE)
	{
	  completionPercent = COMPLETE;
	  completed = true;
	  underConstruction = false;
	  std::cout << "Construction completed" << std::endl;
	}
    }
}

bool Structure::canStartWork()
{
  if (completed || underConstruction || needMats)
    {
      return false;
    }
  else
    {
      return true;
    }
}

bool Structure::isUnderConstruction()
{
  return underConstruction;
}

bool Structure::isCompleted()
{
  return completed;
}

bool Structure::canHaveOwner()
{
  if (ownable)
    {
      if (owner == NULL)
	{
	  return true;
	}
      else
	{
	  return false;
	}
    }
  else
    {
      return false;
    }
}

void Structure::changeOwner(Entity* newOwner)
{
  owner = newOwner;
}

void Structure::structureReport()
{
  std::cout << "Type: " << structType << std::endl;
  if (completed)
    {
      std::cout << "Built" << std::endl;
    }
  else
    {
      std::cout << completionPercent << "% completed" << std::endl;
    }
}

void Structure::startConstruction()
{
  if (!completed)
    {
      if (completionPercent == 0)
	{
	  std::cout << "Starting construction" << std::endl;
	}
      else
	{
	  std::cout << "Resuming construction" << std::endl;
	}
      underConstruction = true;
    }
  else
    {
      std::cout << "Can't build this, it's already built" << std::endl;
    }
}

void Structure::pauseConstruction()
{
  if (underConstruction)
    {
      underConstruction = false;
    }
  else
    {
      std::cout << "Can't pause construction: Object not currently under construction" << std::endl;
    }
}
