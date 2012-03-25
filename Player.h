#ifndef _PLAYER_H
#define _PLAYER_H

#include "btBulletDynamicsCommon.h"

#include "Loader.h"
#include "Model.h"
#include "Entity.h"

class Player
{
 public:

  typedef struct
  {
    float x,y,z;
    float nx,ny,nz;
    float u,v;
  }
  Vertex;
  Player();
  Player(Model*);

  void initPlayer();

  btCollisionShape* getPlayerCollisionShape();
  btDefaultMotionState* getPlayerMotionState();
  btRigidBody* getPlayerRigidBody();
  Model::modelData* getPlayerModelDataPtr();
  std::vector<Vertex>* getVerticesPtr();
  //Entity* getPlayerEntity();

 private:
  btCollisionShape* playerCollision;
  btDefaultMotionState* playerMotionState;
  btRigidBody* playerBody;
  Model::modelData mData;
  Model* playerModel;
  std::vector<Vertex> vertices;
  //Entity playerEntity;

  void modelDataToVertices();
  
};
#endif //PLAYER_H
