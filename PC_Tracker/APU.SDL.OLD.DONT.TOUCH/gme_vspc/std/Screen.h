#pragma once
#include "report.h"

#define SCREEN_X_OFFSET 0
#define SCREEN_Y_OFFSET 50
// should be inside of Main_Memory_View .. but keeping it here for now while I do other things
#define MEMORY_VIEW_X  16 + SCREEN_X_OFFSET
#define MEMORY_VIEW_Y  40 + SCREEN_Y_OFFSET

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern const int PORTTOOL_X;
extern const int PORTTOOL_Y;

extern const int PORTTOOL_PORT0_X;
extern const int PORTTOOL_PORT3_X_RIGHTMOST_LOBYTE;
//
extern const int MOUSE_HEXDUMP_START_X;

extern const int MOUSE_HEXDUMP_END_X;
extern const int MOUSE_HEXDUMP_END_Y;
extern const int MOUSE_HEXDUMP_ENTRY_X_INCREMENT;
extern const int MOUSE_HEXDUMP_ENTRY_Y_INCREMENT;
//
extern const int INFO_X;
extern const int INFO_Y;                                        
//


#define LOCKED_STR "locked"

namespace Screen
{
  //typedef SDL_Rect coord;
  #define NO_INIT 0
  extern SDL_Rect voice0vol;   // = {NO_INIT, NO_INIT,+8+125,10};
  extern SDL_Rect voice0pitch; // = {NO_INIT,NO_INIT, 2*8,8 };
  extern SDL_Rect locked;      // = { MEMORY_VIEW_X+520+24*8, 0 ,(strlen(LOCKED_STR)*8)+1, 9};
  extern SDL_Rect echoE;
  #undef UN_INIT
}