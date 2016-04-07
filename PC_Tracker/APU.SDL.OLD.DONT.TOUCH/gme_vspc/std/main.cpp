#include "app.h"
#include "Screen.h"
#include "Colors.h"
#include "Organization.h"

#include "Render_Context.h"

int init_sdl(SDL_Window **sdlWindow, SDL_Renderer **sdlRenderer, SDL_Texture **sdlTexture,
  SDL_Surface **screen, int width, int height);

int main(int argc, char **argv)
{
  init_sdl(&Render_Context::sdlWindow, &Render_Context::sdlRenderer, 
    &Render_Context::sdlTexture, &Render_Context::screen, SCREEN_WIDTH, SCREEN_HEIGHT);

  Render_Context::windowID = SDL_GetWindowID(Render_Context::sdlWindow);
  //SDL_SetWindowSize(Render_Context::sdlWindow, 1024+100, 768+100);

  //fprintf(stderr, "screen = %d\n", Render_Context::screen);
  App app(argc, argv, 32000);
  app.run();
}


int init_sdl(SDL_Window **sdlWindow, SDL_Renderer **sdlRenderer, SDL_Texture **sdlTexture, 
  SDL_Surface **screen, int width, int height)
{
  Uint32 flags=0;
  flags |= SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER; 

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










