#include "DudeGroup.h"

#include <iostream>

DudeGroup::DudeGroup()
{
  std::cout << "Creating new dudegroup" << std::endl;
}

void DudeGroup::addToGroup(Entity* supplicant)
{
  members.push_back(supplicant);
}

void DudeGroup::removeFromGroup(Entity* trouble)
{

  bool found = false;
  std::vector<Entity*>::iterator it;
  for (it = members.begin(); it != members.end(); ++it)
    {
      if (*it == trouble)
	{	  
	  members.erase(it);
	  found = true;
	}
    }
  if (found)
    {
      std::cout << "Dude removed from group" << std::endl;
    }
  else
    {
      std::cout << "Dude not found in group" << std::endl;
    }
}
