#ifndef _BRAIN_H
#define _BRAIN_H

class Entity;

enum e_brainState
  {
    e_idle,
    e_getFood,
    e_getWater,
    e_takeNap
  };

class Brain
{

  // This brain is the very basicest of brains. It is only really meant to deal with the 
  // Most basic of survival stuff, other more complicated brains are likely to have more 
  // Interesting thought processes. 

 public:
  Brain();
  virtual ~Brain();

  e_brainState runFrame(Entity* caller);

 private:
  e_brainState currentState;
};

#endif //BRAIN_H
