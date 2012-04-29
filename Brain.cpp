#include "Brain.h"

#include <iostream>
#include "Entity.h"

Brain::Brain()
{
  currentSituation.survival.hunger = 0;
  currentSituation.survival.thirst = 0;
  currentSituation.survival.tired = 0;
  currentSituation.work = 0;
  currentSituation.entertainment = 0;
}

Brain::~Brain()
{
}

int Brain::evaluateWork(Brain::s_brainBox situation)
{
  int needHome = (situation.hasHome ? 0 : 1500);
  int buildHome = (situation.homeBuilt ? 0 : 1000);
  return needHome + buildHome;
}

e_brainState Brain::runFrame(Brain::s_brainBox situation)
{

  int hunger = situation.survival.hunger;
  int thirst = situation.survival.thirst;
  int tired = situation.survival.tired;
  int survivalNeeds = 0;
  
  currentSituation.survival.hunger = hunger;
  currentSituation.survival.thirst = thirst;
  currentSituation.survival.tired = tired;

  survivalNeeds = hunger + thirst + tired;
  currentSituation.work = evaluateWork(situation);
  currentSituation.entertainment = 0;

  e_brainState newState = currentState;

  if (survivalNeeds >= currentSituation.work)
    {     
      if (tired < 370)
	newState = e_idle;
      if (thirst > 500)
	newState = e_getWater;
      if (hunger > 500)
	newState = e_getFood;
      if (thirst < 500 && hunger < 500)
	newState = e_idle;
      if (tired > 800)
	newState = e_takeNap;     
    }
  else
    {      
      newState = makeDecision(situation);
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

e_brainState Brain::makeDecision(s_brainBox situation)
{
  if (situation.hasHome)
    {
      if (!situation.homeBuilt || situation.homeBuilding)
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
