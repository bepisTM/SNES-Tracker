#pragma once
#include "SDL.h"
#include "report.h"
#include "gme/player/Music_Player.h"

// TRY NOT TO USE THIS!!! 
// just for prototyping!
//namespace globals


#define LOCKED_STR "locked"

void handle_error( const char* );

namespace mouse {
  extern int x,y;
  extern char show;
}



//extern  //=-1;

#define PACKAGE "spcview"
#define VERSION "0.01"



#define INFO_X      540
#define INFO_Y      420 + 40

// 5 minutes default
#define DEFAULT_SONGTIME  (60*5) 

#define PROG_NAME_VERSION_STRING "vspcplay v1.32 by bazz & Raph Assenat!"
#define CREDITS "APU emulation code from Blargg's GME and Snes_Spc 0.9.0"