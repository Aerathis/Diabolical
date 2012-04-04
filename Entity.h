#ifndef _ENTITY_H
#define _ENTITY_H

#include <string>
#include <vector>

#include "Map.h"

class Entity
{

 public:

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

  void runFrame(Map<double>* world, Map<int>* weather);

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
};

#endif //ENTITY_H
