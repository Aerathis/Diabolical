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
    std::string name;
  };

  Entity();

  void initEntity(int x, int y, int id, std::string name);
  
  s_vitals getVitals();
  s_stats getStats();
  s_skills getSkills();

 private:
  s_vitals vitals;
  s_stats stats;
};

#endif //ENTITY_H
