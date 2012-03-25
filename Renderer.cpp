#include <iostream>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#define GL_GLEXT_PROTOTYPES
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "Renderer.h"


bool Renderer::initRenderer(SDL_Surface* inSurf)
{
  inSurf = surface;
  /*
  SDL_Window* mainwindow;
  SDL_GLContext maincontext;

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
  */
  
  if ((surface = SDL_SetVideoMode(640,480,32, SDL_HWSURFACE|SDL_GL_DOUBLEBUFFER|SDL_OPENGL)) == NULL)
    {
      return false;
    }
  
  /*
  mainwindow = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  if (!mainwindow)
    std::cout << "Unable to create window" << std::endl;
  maincontext = SDL_GL_CreateContext(mainwindow);
  */

  std::cout << "OpenGL initialized" << std::endl;
  glClearColor(0,0,0,0);
  glClearDepth(1.0f);
  glViewport(0,0,640,480);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0,640,480,0,1,-1);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_TEXTURE_2D);
  glLoadIdentity();

  //glGenBuffersARB(1, &playerVBO);

  return true;
}


void Renderer::testRenderer()
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glBegin(GL_QUADS);
  glColor3f(1,0,0); glVertex3f(0,0,0);
  glColor3f(1,1,0); glVertex3f(100,0,0);
  glColor3f(1,0,1); glVertex3f(100,100,0);
  glColor3f(1,1,1); glVertex3f(0,100,0);
  glEnd();

  SDL_GL_SwapBuffers();
}

void Renderer::testRenderPlayer(Player* testEnt)
{
  std::vector<Player::Vertex>* playerVertices = testEnt->getVerticesPtr();
  std::vector<Player::Vertex>::iterator vIt;
  Player::Vertex vertex;


  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  //glTranslatef(320,240,0);
  glBegin(GL_QUADS);
  vIt = playerVertices->begin();
  /*
  for (vIt = playerVertices->begin(); vIt != playerVertices->end(); ++vIt)
    {
      Player::Vertex vertex = *vIt;
      glColor3f(1,0,0); glVertex3f(vertex.x, vertex.y, vertex.z);
    }
  */
  vertex = *vIt;
  //glColor3f(1,1,0); glVertex3f(vertex.x,vertex.y,vertex.z);
  glColor3f(1,1,0); glVertex3f(100,100,0);
  ++vIt;
  vertex = *vIt;
  //glColor3f(1,0,1); glVertex3f(vertex.x,vertex.y,vertex.z);
  glColor3f(1,0,0); glVertex3f(200,100,0);
  ++vIt;
  vertex = *vIt;
  //glColor3f(1,1,1); glVertex3f(vertex.x,vertex.y,vertex.z);
  glColor3f(1,0,1); glVertex3f(200,200,0);
  ++vIt;
  vertex = *vIt;
  //glColor3f(1,1,1); glVertex3f(vertex.x, vertex.y, vertex.z);
  glColor3f(1,1,1); glVertex3f(100,200,0);
  glEnd();
  SDL_GL_SwapBuffers();
}
