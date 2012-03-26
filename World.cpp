#include "World.h"

#include "Creators.h"

World::World()
{
  collisionConfiguration = NULL;
  dispatcher = NULL;
  overlappingPairCache = NULL;
  solver = NULL;
  dynamicsWorld = NULL;
  player = new Player();
}

void World::initWorld()
{
  collisionConfiguration = new btDefaultCollisionConfiguration();
  dispatcher = new btCollisionDispatcher(collisionConfiguration);
  overlappingPairCache = new btDbvtBroadphase();
  solver = new btSequentialImpulseConstraintSolver;
  dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver,
					      collisionConfiguration);
  dynamicsWorld->setGravity(btVector3(0,-10,0));

  worldMap.setSize(0);
  worldWeather.setWeatherMapSize(0);
}

btDiscreteDynamicsWorld* World::getWorld()
{
  return dynamicsWorld;
}

void World::registerPlayer()
{
  player->initPlayer();
  std::cout << "Beginning registerPlayer" << std::endl;
  dynamicsWorld->addRigidBody(player->getPlayerRigidBody());
  std::cout << "Rigid body added to world" << std::endl;
}

Player* World::getPlayerPtr()
{
  return player;
}

void World::runFrame()
{
  worldWeather.runFrame();
}

void World::runFrameWithInput(SDL_Event* Event)
{
  //If the event is a click on a unit or structure then we set it as the selected entity
  if (Event->type == SDL_KEYDOWN)
    {
      if(Event->key.keysym.sym==SDLK_c)
	{
	  worldMap.setSize(10);
	  worldWeather.setWeatherMapSize(10);
	  creators::fillTerrain(&worldMap);
	}
    }
}
