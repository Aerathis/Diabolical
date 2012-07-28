#ifndef _RENDERER_H
#define _RENDERER_H

#include <GL/gl.h>

#include "World.h"

class Renderer
{

 public:
  static void renderTest();

	static void renderTerrain(World* inWorld);	

};

#endif //RENDERER_H
