
#include "Loader.h"
#include "Model.h"
#include "Player.h"

Player::Player()
{
}

Player::Player(Model* inModel)
{
  playerModel = inModel;

  playerCollision = new btSphereShape(btScalar(1.f));
  btTransform startTransform;
  startTransform.setIdentity();
  btScalar mass(playerModel->getMass());
  bool isDynamic = (mass != 0.f);
  btVector3 localInertia(0,0,0);

  if (isDynamic)
    playerCollision->calculateLocalInertia(mass,localInertia);

  startTransform.setOrigin(btVector3(0,0,0));
  playerMotionState = new btDefaultMotionState(startTransform);
  btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,playerMotionState,playerCollision,localInertia);
  playerBody = new btRigidBody(rbInfo);
}

void Player::modelDataToVertices()
{
  std::vector<float>::iterator vIt, nIt;
  std::vector<float> vertvec = mData.geometry.rawVertices;
  std::vector<float> normvec = mData.geometry.rawNormals;
  
  for (vIt = vertvec.begin(); vIt != vertvec.end(); ++vIt)
    {
      
      Vertex temp = {0};

      float x = *vIt;
      ++vIt;
      float y = *vIt;
      ++vIt;
      float z = *vIt;
      
      temp.x = x;
      temp.y = y;
      temp.z = z;
      temp.nx = 0.f;
      temp.ny = 0.f;
      temp.nz = 0.f;
      temp.u = 0.f;
      temp.v = 0.f;

      vertices.push_back(temp);
    }

  std::vector<Vertex>::iterator vertIt = vertices.begin();

  for (nIt = normvec.begin(); nIt != normvec.end(); ++nIt)
    {
      
      Vertex tVert = *vertIt;

      float nx = *nIt;
      ++nIt;
      float ny = *nIt;
      ++nIt;
      float nz = *nIt;

      tVert.nx = nx;
      tVert.ny = ny;
      tVert.nz = nz;
      
      ++vertIt;
    }

}

void Player::initPlayer()
{
  
  Loader::loadModel("../../assets/player.dae",&mData);
  playerModel = new Model(&mData);

  modelDataToVertices();

  playerCollision = new btSphereShape(btScalar(1.f));
  btTransform startTransform;
  startTransform.setIdentity();
  btScalar mass(playerModel->getMass());
  bool isDynamic = (mass != 0.f);
  btVector3 localInertia(0,0,0);
  if (isDynamic)
    playerCollision->calculateLocalInertia(mass, localInertia);
  
  startTransform.setOrigin(btVector3(0,0,0));
  playerMotionState = new btDefaultMotionState(startTransform);
  btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,playerMotionState,playerCollision,localInertia);
  playerBody = new btRigidBody(rbInfo);
}

btCollisionShape* Player::getPlayerCollisionShape()
{
  return playerCollision;
}

btDefaultMotionState* Player::getPlayerMotionState()
{
  return playerMotionState;
}

btRigidBody* Player::getPlayerRigidBody()
{
  return playerBody;
}

Model::modelData* Player::getPlayerModelDataPtr()
{
  return &mData;
}

std::vector<Player::Vertex>* Player::getVerticesPtr()
{
  return &vertices;
}
/*
Entity* Player::getPlayerEntity()
{
  return &playerEntity;
}
*/
