#include <iostream>

#include "CApp.h"

CApp::CApp()
{
  Surf_Display = NULL;
  Running = true;
}

bool CApp::OnInit()
{
  std::cout << "OnInit started" << std::endl;
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
      return false;
    }
  std::cout << "SDL initialized" << std::endl;
  
  if (!renderer.initRenderer(Surf_Display))
    {
      return false;
    }
  std::cout << "World init" << std::endl;
  gameWorld.initWorld();
  std::cout << "World init complete" << std::endl;
  std::cout << "Registering player" << std::endl;
  gameWorld.registerPlayer();
  std::cout << "Player registered" << std::endl;

  return true;
}

void CApp::OnLoop()
{
  gameWorld.runFrame();
}

void CApp::OnRender()
{
  //renderer.testRenderer();
  renderer.testRenderPlayer(gameWorld.getPlayerPtr());
}
void CApp::OnEvent(SDL_Event* Event)
{
  if (Event->type == SDL_QUIT)
    {
      Running = false;
    }
  else
    {
      gameWorld.runFrameWithInput(Event);
    }
}

void CApp::OnCleanup()
{
  SDL_Quit();
}

int CApp::OnExecute()
{
  if(OnInit() == false)
    {
    return -1;
    }

  SDL_Event Event;

  while (Running)
    {
      while(SDL_PollEvent(&Event))
	{
	  OnEvent(&Event);
	}
      OnLoop();
      OnRender();
    }
  OnCleanup();
  return 0;
}

int main(int argc, char** argv)
{
  CApp theApp;
  return theApp.OnExecute();
}
