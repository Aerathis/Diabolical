#include "Renderer.h"

#include <iostream>

void Renderer::renderTest()
{
  glClearColor(0.0,0.0,0.0,0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  //glBegin(GL_QUADS);
  //glColor3f(1,0,0);glVertex3f(0,0,0);
  //glColor3f(0,1,0);glVertex3f(100,0,0);
  //glColor3f(0,0,1);glVertex3f(100,100,0);
  //glColor3f(1,1,1);glVertex3f(0,100,0);
  //glEnd();
  glFlush();
}

void Renderer::renderTerrain(World* inWorld) 
{
	Map<double>* heightMap = inWorld->im_getWorldMap();
}
