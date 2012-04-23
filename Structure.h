#ifndef _STRUCTURE_H
#define _STRUCTURE_H

#include <map>

#include "Object.h"

class Entity;

class Structure : public Object
{
 public:
  enum e_structType
  {
    e_home
  };

  enum e_materialType
  {
    e_wood,
    e_stone
  };

  Structure();
  
  void runFrame();
  bool canStartWork();
  bool isUnderConstruction();
  bool isCompleted();
  bool canHaveOwner();
  void changeOwner(Entity* newOwner);
  void startConstruction();
  void pauseConstruction();

  void structureReport();

 private:
  e_structType structType;
  int completionPercent;
  int constructionTimeScale;
  bool completed;
  bool underConstruction;
  bool ownable;
  std::map<e_materialType,int> materialReqs;
  
  Entity* owner;
};

#endif //STRUCTURE_H
