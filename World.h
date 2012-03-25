#ifndef _WORLD_H
#define _WORLD_H

#include <SDL/SDL.h>

#include <vector>

#include "btBulletDynamicsCommon.h"

#include "../../../tools/xorshift.h"

#include "Entity.h"
#include "Map.h"
#include "Player.h"
#include "Weather.h"

class World
{

 private:
  btAlignedObjectArray<btCollisionShape*> collisionShapes;
  btDefaultCollisionConfiguration* collisionConfiguration;
  btCollisionDispatcher* dispatcher;
  btBroadphaseInterface* overlappingPairCache;
  btSequentialImpulseConstraintSolver* solver;
  btDiscreteDynamicsWorld* dynamicsWorld;

  ShiftRand randGen;

  Player* player;
  Entity* selected;

  std::vector<Entity> citizens;
  Map<int> worldMap;
  Weather worldWeather;

 public:
  World();
  void initWorld();
  
  btDiscreteDynamicsWorld* getWorld();
  Player* getPlayerPtr();

  void registerPlayer();

  void runFrame();
  void runFrameWithInput(SDL_Event* Event);

};

#endif //WORLD_H
