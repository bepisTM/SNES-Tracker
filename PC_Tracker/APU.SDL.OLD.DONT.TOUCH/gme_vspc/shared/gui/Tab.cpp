#include "gui/Tab.h"
#include "Colors.h"
#include "DEBUGLOG.h"

int Tab::horiz_pixel_length()
{
  return str.length()*CHAR_WIDTH + pad_w_size*2;
}

void Tab::draw(SDL_Surface *screen/*=Render_Context::screen*/, bool active/*=false*/)
{
  Uint32 *bg_color, *fg_color;

  if (active) 
  {
    //DEBUGLOG("weewr");
    bg_color = &Colors::Interface::color[Colors::Interface::active_tab_bg];
    fg_color = &Colors::Interface::color[Colors::Interface::active_tab_fg];
  }
  else
  {
    //DEBUGLOG("insactive");
    bg_color = &Colors::Interface::color[Colors::Interface::inactive_tab_bg];
    fg_color = &Colors::Interface::color[Colors::Interface::inactive_tab_fg];
  }

  SDL_FillRect(screen, &rect, *bg_color);
  sdlfont_drawString(screen, rect.x+pad_w_size, rect.y+pad_h_size, str.c_str(), *fg_color, 
    *bg_color);
}

Tab::Tab() : Clickable_Rect_Id(NULL,NULL)
{ }

Tab::Tab(int x, int y, int pad_size, std::string str, 
  int (*action)(void *data,int id)/*=NULL*/, void *data/*=NULL*/) : 
Clickable_Rect_Id(action,data),
str(str),
pad_w_size(pad_size),
pad_h_size(pad_size)
{
  rect.x = x;
  rect.y = y;
  rect.w = pad_size + str.length()*CHAR_WIDTH + pad_size;
  rect.h = pad_size + CHAR_HEIGHT + pad_size;
}

Tab::Tab(int x, int y, int pad_w_size, int pad_h_size, std::string str,
  int (*action)(void *data, int id)/*=NULL*/, void *data/*=NULL*/) : 
Clickable_Rect_Id(action,data),
str(str),
pad_w_size(pad_w_size),
pad_h_size(pad_h_size)
{
  rect.x = x;
  rect.y = y;
  rect.w = pad_w_size + str.length()*CHAR_WIDTH + pad_w_size;
  rect.h = pad_h_size + CHAR_HEIGHT + pad_h_size;
}

Tab::Tab(int pad_w_size, int pad_h_size, std::string str,
  int (*action)(void *data, int id)/*=NULL*/, void *data/*=NULL*/) : 
Clickable_Rect_Id(action,data),
str(str),
pad_w_size(pad_w_size),
pad_h_size(pad_h_size)
{
  rect.w = pad_w_size + str.length()*CHAR_WIDTH + pad_w_size;
  rect.h = pad_h_size + CHAR_HEIGHT + pad_h_size;
}