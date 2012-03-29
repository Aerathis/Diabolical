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
    s_skills skills;
  };

  struct s_vitals
  {
    float x;
    float y;
    int id;
    int timeAlive;
    int coreTemp;
    std::string name;
  };

  Entity();

  void initEntity(int x, int y, int id, std::string name);

  void runFrame();
  
  s_vitals getVitals();
  s_stats getStats();
  s_skills getSkills();


  void testLocChange(int newX);

 private:
  s_vitals vitals;
  s_stats stats;
};

#endif //ENTITY_H
