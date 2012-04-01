#ifndef _ENTITY_H
#define _ENTITY_H

#include <string>
#include <vector>

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

  void runFrame();

  void moveToTargetLocation(int x, int y);
  void moveToTarget(Entity* targ);
  
  s_vitals getVitals();
  s_stats getStats();
  s_skills getSkills();


  void testLocChange(int newX);

 private:
  s_vitals vitals;
  s_stats stats;

  float targetX, targetY;
  Entity* target;
};

#endif //ENTITY_H
