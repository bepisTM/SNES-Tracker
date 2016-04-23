#include "sdl.h"

int init_sdl()
{
  Uint32 flags = SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER; 

  if (SDL_Init(flags) != 0) 
  {
    fprintf(stderr,"\nUnable to initialize SDL:  %s\n", SDL_GetError());
    return -1;
  }

  atexit(SDL_Quit);

  return 0; 
}
