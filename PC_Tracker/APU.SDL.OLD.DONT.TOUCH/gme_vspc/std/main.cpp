#include "app.h"
#include "Screen.h"
#include "Colors.h"
#include "Organization.h"

#include "Render_Context.h"

int init_sdl();

int main(int argc, char **argv)
{
  init_sdl();

  App app(argc, argv, 32000);
  app.run();
}


int init_sdl()
{
  Uint32 flags = SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER; 

  if (SDL_Init(flags) != 0) 
  {
    fprintf(stderr,
            "\nUnable to initialize SDL:  %s\n",
            SDL_GetError()
           );
    return -1;
  }

  atexit(SDL_Quit);
  
  Colors::precompute(*screen);

  dblclick::init();

  return 0; 
}










