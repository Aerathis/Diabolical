#include "World.h"

#include "Creators.h"

World::World()
{
  // Normal constructor business. Nulling things out and all that.
  collisionConfiguration = NULL;
  dispatcher = NULL;
  overlappingPairCache = NULL;
  solver = NULL;
  dynamicsWorld = NULL;
  player = new Player();
}

void World::initWorld()
{
  // Initializing the world parameters, at the moment there's no method to use anything but these defaults. 
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
  // Get the player set up in the world. (Even though I don't use the rigid body for anything).
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
  // The update function, this is going to be run when there's no input
  worldWeather.runFrame();
}

void World::runFrameWithInput(SDL_Event* Event)
{
  // The other update function, this is going to be run when there is input. 
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

  runFrame();
}
