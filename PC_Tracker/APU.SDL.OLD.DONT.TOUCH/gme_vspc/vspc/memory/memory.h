#pragma once

#include "SDL.h"
#include "gme/player/Music_Player.h"
#include "Debugger_Base.h"
#include "gui/cursor.h"

struct Memory : public Debugger_Base
{
  Memory(Music_Player *cplayer, SDL_Surface *cscreen);

  void set_addr(int i);
  void add_addr(int i);

  enum submodes { HARD_EDIT=0, EASY_EDIT=1 };

  //static Mem_Cursor memcursor;
  static Cursor cursor;

  static Music_Player *player;
  static SDL_Surface *screen;
  static uint8_t *IAPURAM;
  static Uint16 address; //=0x0000;
  static Uint16 addr_being_edited;
  static int rel_x;
  static int rel_y;

  static int res_x;
  static int res_y;
};