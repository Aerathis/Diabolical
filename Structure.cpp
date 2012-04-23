#include "Structure.h"

#include <iostream>

Structure::Structure() : Object(Object::e_structure)
{
  structType = e_home;
  completionPercent = 0;
  constructionTimeScale = 1;
  completed = false;
  underConstruction = false;
}

void Structure::runFrame()
{
  if (underConstruction)
    {
      completionPercent += 1 * constructionTimeScale;
      if (completionPercent >= 10000)
	{
	  completionPercent = 10000;
	  completed = true;
	  underConstruction = false;
	  std::cout << "Construction completed" << std::endl;
	}
    }
}

bool Structure::canStartWork()
{
  if (completed || underConstruction)
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
