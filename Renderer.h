#ifndef _RENDERER_H
#define _RENDERER_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

#include "Player.h"

//extern PFNGLGENBUFFERSARBPROC glGenBuffers;

class Renderer
{

 private:

  SDL_Surface* surface;
  GLuint playerVBO;

 public:
  
  Renderer()
    {
      //glGenBuffers = 0;
      //glGenBuffers = (PFNGLGENBUFFERSARBPROC)SDL_GL_GetProcAddress("glGenBuffersARB");
    }
  bool initRenderer(SDL_Surface* surf);

  void testRenderer();
  
  void testRenderPlayer(Player*);

};

#endif //RENDERER_H
