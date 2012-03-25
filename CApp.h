#ifndef _CAPP_H
#define _CAPP_H

#include <SDL/SDL.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "btBulletDynamicsCommon.h"

#include "Renderer.h"
#include "World.h"

#define ASSETPATH "../../assets/"

class CApp {

 private:

  bool Running;
  Renderer renderer;
  SDL_Surface* Surf_Display; 
  World gameWorld;

 public:
  CApp();

  int OnExecute();
  bool OnInit();
  void OnEvent(SDL_Event* Event);
  void OnLoop();
  void OnRender();
  void OnCleanup();
};
#endif //CAPP_H
