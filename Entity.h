#ifndef _ENTITY_H
#define _ENTITY_H

#include <string>
#include <vector>

#include "Brain.h"
#include "Map.h"

class World;

class Entity
{

 public:

  enum e_frameState
  {
    e_eatFood,
    e_drinkWater,
    e_nap,
    e_idleFrame
  };

  struct s_frameResolution
  {
    e_frameState resultState;
    void* target;
  };

  struct s_skills
  {
  };

  struct s_stats
  {
    int hunger;
    int thirst;
    int tired;
    int moveSpeed;
    s_skills skills;
  };

  struct s_vitals
  {
    int x;
    int y;
    int id;
    int timeAlive;
    int coreTemp;
    std::string name;
  };

  Entity();

  void initEntity(int x, int y, int id, std::string name);

  void runFrame(World* host);

  void moveToTargetLocation(int x, int y);
  void moveToTarget(Entity* targ);

  s_vitals getVitals();
  s_stats getStats();
  s_skills getSkills();

 private:
  s_vitals vitals;
  s_stats stats;

  bool alive;
  float targetX, targetY;
  Entity* target;
  Brain smarts;
  e_brainState decision;

  void processDecision(e_brainState decision, World* host, s_frameResolution* result);
  void resolveFrame(s_frameResolution* frState);
};

#endif //ENTITY_H
