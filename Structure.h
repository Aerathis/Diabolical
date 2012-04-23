#ifndef _STRUCTURE_H
#define _STRUCTURE_H

#define COMPLETE 10000

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
  int totalMats;
  bool completed;
  bool underConstruction;
  bool needMats;
  bool ownable;
  std::map<e_materialType,int> materialReqs;
  std::map<e_materialType,int> materialsPresent;
  
  Entity* owner;
};

#endif //STRUCTURE_H
