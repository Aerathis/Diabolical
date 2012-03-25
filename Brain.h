#ifndef _BRAIN_H
#define _BRAIN_H

class Entity;

class Brain
{
 public:
  Brain();
  ~Brain();

  void runFrame(void*);
};

#endif //BRAIN_H
