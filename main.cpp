#include <iostream>

#include <SDL.h>
#include <SDL_opengl.h>

int main(int argc, char** argv)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
      std::cout << "SDL: " << SDL_GetError() << std::endl;
    }
  atexit(SDL_Quit);
  system("PAUSE");
  return 0;
}
