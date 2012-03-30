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
  worldCreated = false;

  worldMap = new Map<double>;
  worldWeather = new Map<int>;
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

  worldMap->setSize(0);
  worldWeather->setSize(0);

  selected = NULL;
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
  //worldWeather.runFrame();
  std::vector<Entity>::iterator it;
  for (it = citizens.begin(); it != citizens.end(); ++it)
    {
      it->runFrame();
    }
}

void World::runFrameWithInput(SDL_Event* Event)
{
  // The other update function, this is going to be run when there is input. 
  // If the event is a click on a unit or structure then we set it as the selected entity
  if (Event->type == SDL_KEYDOWN)
    {
      if(Event->key.keysym.sym==SDLK_c)
	{
	  if (!worldCreated)
	    {
	      worldMap->setSize(10);
	      worldWeather->setSize(10);
	      creators::fillTerrain(worldMap);
	      creators::fillWeather(worldWeather);
	      worldCreated = true;
	    }
	  else if(worldCreated)
	    {
	      Entity newEnt;
	      newEnt.initEntity(0,0,0,"test");
	      std::cout << "New Entity created" << std::endl;
	      citizens.push_back(newEnt);
	      std::cout << "Entity added to citizens" << std::endl;
	    }
	}
      else if (Event->key.keysym.sym == SDLK_p)
	{
	  if (selected)
	    {
	      std::cout << "Selected report" << std::endl;
	      std::cout << "Position: (";
	      std::cout << selected->getVitals().x << "," << selected->getVitals().y << ")";
	      std::cout << " Time Alive: " << selected->getVitals().timeAlive;
	      std::cout << " Hungry: " << selected->getStats().hunger << std::endl;
	    }
	}
      else if (Event->key.keysym.sym == SDLK_s)
	{
	  std::cout << "Clearing Selection" << std::endl;
	  selected = NULL;
	}
      else if (Event->key.keysym.sym == SDLK_1)
	{
	  if (citizens.size() >= 1 && selected != &citizens[0])
	    {
	      selected = &citizens[0];
	      std::cout << "First entity selected" << std::endl;
	    }
	}
      else if (Event->key.keysym.sym == SDLK_2)
	{
	  if (citizens.size() >= 2 && selected != &citizens[1])
	    {
	      selected = &citizens[1];
	      std::cout << "Second entity selected" << std::endl;
	    }
	}
      else if (Event->key.keysym.sym == SDLK_w)
	{
	}
      else if (Event->key.keysym.sym == SDLK_t)
	{
	  std::cout << worldMap->getLocationAtCoord(5,0) << std::endl;
	  std::cout << worldWeather->getLocationAtCoord(5,0) << std::endl;
	}
    }
  runFrame();ss
}
