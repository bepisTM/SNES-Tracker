#pragma once

#include "SDL.h"
#include "sdl_userevents.h"
#include "gui/cursor.h"

#define MOUSE_HEXDUMP_START_X 584
#define MOUSE_HEXDUMP_START_Y 229
#define MOUSE_HEXDUMP_END_X 740
#define MOUSE_HEXDUMP_END_Y 364 + 9
#define MOUSE_HEXDUMP_ENTRY_X_INCREMENT 20 // but i think i like 16 programmatically
#define MOUSE_HEXDUMP_ENTRY_Y_INCREMENT 9  // dunno what i like programmatically yet



extern int hexdump_address;
extern struct SIAPU IAPU;
namespace mouse_hexdump
{
  int rel_x; // = te->motion.x - MOUSE_HEXDUMP_START_X;
  //rel_x+=2;
  int rel_y; // = te->motion.y - MOUSE_HEXDUMP_START_Y;

  int res_x;
  int res_y;
  Uint8 highnibble;
  Uint8 horizontal=1;

  void inc_cursor_row()
  {
    cursor::toggle=1;
    
    if (res_y == 15)
    {
      //res_y;
      hexdump_address += 8;
    }
    else res_y++;    
  }
  void dec_cursor_row()
  {
    cursor::toggle=1;
    
    if (res_y == 0)
    {
      //res_y;
      hexdump_address -= 8;
    }
    else res_y--;    
  }
  void inc_cursor_pos()
  {
    cursor::toggle=1;
    if (highnibble)
    {
      highnibble = 0;
    }
    else
    {
      if (res_x == 7)
      {
        res_x = 0;
        if (res_y == 15)
        {
          //res_y;
          hexdump_address += 8;
        }
        else res_y++;


      }
      else
        res_x++;

      highnibble = 1;
    }
  }
  void dec_cursor_pos()
  {
    cursor::toggle=1;
    if (!highnibble)
    {
      highnibble = 1;
    }
    else
    {
      if (res_x == 0)
      {
        res_x = 7;
        if (res_y == 0)
        {
          //res_y;
          hexdump_address -= 8;
        }
        else res_y--;
      }
      else
        res_x--;

      highnibble = 0;
    }
  }

  void draw_cursor(SDL_Surface *screen, Uint32 color)
  {
    if (mouse_hexdump::highnibble)
    {
      cursor::draw(screen, MOUSE_HEXDUMP_START_X + (mouse_hexdump::res_x * MOUSE_HEXDUMP_ENTRY_X_INCREMENT), MOUSE_HEXDUMP_START_Y + (mouse_hexdump::res_y * MOUSE_HEXDUMP_ENTRY_Y_INCREMENT), color);
    }
    else
    {
      cursor::draw(screen, MOUSE_HEXDUMP_START_X + (mouse_hexdump::res_x * MOUSE_HEXDUMP_ENTRY_X_INCREMENT + (7)), MOUSE_HEXDUMP_START_Y + (mouse_hexdump::res_y * MOUSE_HEXDUMP_ENTRY_Y_INCREMENT), color);
    }
  }

}