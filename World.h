#ifndef _WORLD_H
#define _WORLD_H

#include <SDL/SDL.h>

#include <vector>

#include "btBulletDynamicsCommon.h"

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

  Player* player;
  Entity* selected;

  std::vector<Entity> citizens;
  Map<double> worldMap;
  Map<int> worldWeather;

  bool worldCreated;

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
