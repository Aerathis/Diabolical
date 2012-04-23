#ifndef _STRUCTURE_H
#define _STRUCTURE_H

#include "Object.h"

class Structure : public Object
{
 public:
  enum e_structType
  {
    e_home
  };

  Structure();
  
  void runFrame();
  bool canStartWork();
  bool isUnderConstruction();
  bool isCompleted();
  void startConstruction();
  void pauseConstruction();

  void structureReport();

 private:
  e_structType structType;
  int completionPercent;
  int constructionTimeScale;
  bool completed;
  bool underConstruction;
};

#endif //STRUCTURE_H
