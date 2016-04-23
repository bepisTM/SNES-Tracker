#pragma once
#include "SDL.h"
#include "Experience.h"
#include <string>
#include "Render_Collection.h"


struct Window : public Experience
{
  void init();
  Window(int width, int height, const char *title);
  ~Window();
  Render_Collection rc;

  Uint32 windowID=0;
  SDL_Window *sdlWindow = NULL;

  
  std::string title;

  bool is_focused=false;

  void clear_screen();
  void update_screen();

  void show();
  void raise();
  void hide();
  void destroy();

  void set_title(const char *str);

  bool oktoshow = false;
};