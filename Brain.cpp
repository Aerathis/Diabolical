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
  if (caller->getStats().thirst > 50)
    {
      newState = e_getWater;
    }
  if (caller->getStats().hunger > 50)
    {
      newState = e_getFood;
    }
  if (caller->getStats().thirst < 10 && caller->getStats().hunger < 10)
    {
      newState = e_idle;
    }
  if (caller->getStats().tired > 70)
    {
      newState = e_takeNap;
    }

  if (newState != currentState)
    {
      std::cout << "Brain state changed" << std::endl;
      std::cout << "New State: " << newState << std::endl;
      currentState = newState;
    }

  return currentState;
}
