
#pragma once
#include "SDL.h"
#include "globals.h"

#include "report.h"
#include "Voice_Control.h"
#include <math.h>
#include "sdl_dblclick.h"
#include "Port_Tool.h"
#include "Mouse_Hexdump_Area.h"
#include "Main_Memory_Area.h"
#include "Colors.h"
#include "platform.h"
#include "Main_Window.h"
#include "gui/Window.h"

typedef Uint32 SDL_WindowID_Type;

struct Debugger : public BaseD
{
public:
  Debugger(int &argc, char **argv); // , Music_Player *player, SDL_Window *, SDL_Renderer *, SDL_Texture *, SDL_Surface*);
  ~Debugger();
  void run();
  void handle_events();

  SDL_DisplayMode monitor_display_mode;
  //
  //std::map<SDL_WindowID_Type, Window *> window_map;
  Experience *exp = NULL, *sub_window_experience = NULL;
  
  Main_Window main_window;
  Options_Window options_window;
  Spc_Export_Window spc_export_window;
  static const int NUM_WINDOWS = 3;
  Window *window_map[NUM_WINDOWS+1];  // there's a REASON for +1 (extra NULL item)

  Cursors cursors;
};

