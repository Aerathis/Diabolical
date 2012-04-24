#include "Brain.h"

#include <iostream>
#include "Entity.h"

Brain::Brain()
{
}

Brain::~Brain()
{
}

e_brainState Brain::runFrame(Entity* caller)
{
  e_brainState newState = currentState;
  // Cycle through various extremely basic scenarios and select a decision
  if (caller->getStats().tired < 370)
    {
      newState = e_idle;
    }
  if (caller->getStats().thirst > 500)
    {
      newState = e_getWater;
    }
  if (caller->getStats().hunger > 500)
    {
      newState = e_getFood;
    }
  if (caller->getStats().thirst < 500 && caller->getStats().hunger < 500)
    {
      newState = e_idle;
    }
  if (caller->getStats().tired > 800)
    {
      newState = e_takeNap;
    }

  if (newState == e_idle)
    {
      newState = makeDecision(caller);
    }
  // If the brain has changed its mind since the last time it made a decision
  // it announces that change and applies it to the current decision
  if (newState != currentState)
    {
      std::cout << "Brain state changed" << std::endl;
      std::cout << "New State: " << newState << std::endl;
      currentState = newState;
    }
  return currentState;
}

e_brainState Brain::makeDecision(Entity* caller)
{
  if (caller->hasHome())
    {
      if (caller->getHomePtr()->isUnderConstruction() || !caller->getHomePtr()->isCompleted())
	{
	  return e_buildHome;
	}
      else
	{
	  return e_idle;
	}
    }
  else
    {
      return e_makeHome;
    }
}
