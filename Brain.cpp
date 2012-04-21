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
