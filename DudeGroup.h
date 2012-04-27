#ifndef _DUDEGROUP_H
#define _DUDEGROUP_H

#include <vector>

#include "Entity.h"

class DudeGroup
{
 public:

  DudeGroup();
  
  bool requestEntry(Entity* supplicant);
  void addToGroup(Entity* supplicant);
  void removeFromGroup(Entity* trouble);

 private:
  std::vector<Entity*> members;
};

#endif //DUDEGROUP_H
