#pragma once

struct Render_Collection
{
  void clear_screen()
  {
    SDL_FillRect(screen, NULL, 0);
    SDL_UpdateTexture(sdlTexture, NULL, screen->pixels, screen->pitch);
    SDL_RenderClear(sdlRenderer);
    SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, NULL);
    SDL_RenderPresent(sdlRenderer);
  }
  void update_screen()
  {
    SDL_UpdateTexture(sdlTexture, NULL, screen->pixels, screen->pitch);
    SDL_RenderClear(sdlRenderer);
    SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, NULL);
    SDL_RenderPresent(sdlRenderer);
  }
  void destroy()
  {
    if (screen)
    {
      SDL_FreeSurface(screen);
      screen = NULL;
    }
    if (sdlTexture)
    {
      SDL_DestroyTexture(sdlTexture);
      sdlTexture = NULL;
    }
      
    if (sdlRenderer)
    {
      SDL_DestroyRenderer(sdlRenderer);
      sdlRenderer = NULL;
    }
  }

  
  SDL_Renderer *sdlRenderer = NULL;
  SDL_Texture *sdlTexture = NULL;
  SDL_Surface *screen = NULL;
  SDL_Rect rect;
};