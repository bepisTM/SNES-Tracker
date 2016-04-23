#include "Mouse_Hexdump_Area.h"
int Mouse_Hexdump_Area::MOUSE_HEXDUMP_START_Y;

void Mouse_Hexdump_Area::add_addr(int i)
{
  address += i;
  update_editing_address();
}

void Mouse_Hexdump_Area::update_editing_address()
{
  report::restore_color(addr_being_edited);
  addr_being_edited = address+(res_y*8)+res_x;
  
  if ( IS_SPECIAL_ADDRESSES(addr_being_edited) )
  {
    // only update the buffer the first time.. if we haven't started writing in a new value
    if (!draw_tmp_ram)
    { 
      if (addr_being_edited == 0xf3)
        tmp_ram = player->spc_read(0xf2);
      else tmp_ram = player->spc_read(addr_being_edited);
    }
    if (old_addr != addr_being_edited)
    {
      /* let's talk about old_addr != addr_being_edit.. basically if the user was editing one of these special registers above
      Well those special registers are "careful" where we don't want to submit the value until the whole byte has been explicitly
      set unlike others where we immediately update the hi/lo nibble.. now.. if we were editing one of these special addresses/registers..
      and then we moved on to another address.. this logic will reset the tmpram boolean and update the tmpram value...*/
      draw_tmp_ram=0;
    }
  }
}
void Mouse_Hexdump_Area::inc_cursor_row()
{
  old_addr = addr_being_edited;
  cursor.toggle=1;
  
  if (res_y == 15)
  {
    add_addr(+8);
  }
  else res_y++;    
  update_editing_address();
}
void Mouse_Hexdump_Area::dec_cursor_row()
{
  old_addr = addr_being_edited;
  cursor.toggle=1;
  
  if (res_y == 0)
  {
    add_addr(-8);
  }
  else res_y--;    
  update_editing_address();
}
void Mouse_Hexdump_Area::inc_cursor_pos()
{
  old_addr = addr_being_edited;
  cursor.toggle=1;
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
        add_addr(8);
      }
      else res_y++;


    }
    else
      res_x++;

    highnibble = 1;
  }
  update_editing_address();
}
void Mouse_Hexdump_Area::dec_cursor_pos()
{
  old_addr = addr_being_edited;
  cursor.toggle=1;
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
        add_addr(-8);
      }
      else res_y--;
    }
    else
      res_x--;

    highnibble = 0;
  }
  
  update_editing_address();
}

void Mouse_Hexdump_Area::draw_cursor(SDL_Surface *screen, Uint32 color)
{
  if (highnibble)
  {
    cursor.draw(screen, MOUSE_HEXDUMP_START_X + (res_x * MOUSE_HEXDUMP_ENTRY_X_INCREMENT), MOUSE_HEXDUMP_START_Y + (res_y * MOUSE_HEXDUMP_ENTRY_Y_INCREMENT), color);
  }
  else
  {
    cursor.draw(screen, MOUSE_HEXDUMP_START_X + (res_x * MOUSE_HEXDUMP_ENTRY_X_INCREMENT + (7)), MOUSE_HEXDUMP_START_Y + (res_y * MOUSE_HEXDUMP_ENTRY_Y_INCREMENT), color);
  }
}


