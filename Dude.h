#ifndef _DUDE_H
#define _DUDE_H

#include "Entity.h"
#include "Brain.h"

class Dude : public Entity
{
 private:
  int hungry, thirsty, tired;
  Brain smarts;

 public:
  Dude();
  ~Dude();

  void runFrame();
};

#endif //DUDE_H
