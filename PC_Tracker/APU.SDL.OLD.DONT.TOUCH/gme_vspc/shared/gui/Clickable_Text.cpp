#include "gui/Clickable_Text.h"
#include "utility.h"
#include "sdlfont.h"
#include <assert.h>

Clickable_Text::Clickable_Text() : 
Clickable_Rect(action,data),
str("")
{}

Clickable_Text::Clickable_Text(std::string str, int (*action)(void *data)/*=NULL*/, 
void *data/*=NULL*/,
Uint32 color/*=Colors::Interface::color[Colors::Interface::text_fg]*/) : 
Clickable_Rect(action,data),
str(str),
color(color)
{
  rect.w = str.length()*CHAR_WIDTH; // could add padding
  rect.h = CHAR_HEIGHT;
}
Clickable_Text::Clickable_Text(std::string str, int x, int y, 
int (*action)(void *data)/*=NULL*/, void *data/*=NULL*/) : 
Clickable_Rect(action,data),
str(str)
{
  setup(x,y);
}

void Clickable_Text::setup(int x, int y)
{
  rect.w = str.length()*CHAR_WIDTH; // could add padding
  rect.h = CHAR_HEIGHT;
  rect.x = x;
  rect.y = y;
}

void Clickable_Text::draw(Uint32 &color, bool prefill/*=true*/, 
  bool Vflip/*=false*/, bool Hflip/*=false*/)
{
  sdlfont_drawString(screen, rect.x, rect.y, str.c_str(), color, 
    Colors::Interface::color[Colors::Interface::Type::text_bg], prefill, Vflip, Hflip);
}

void Clickable_Text::draw(bool prefill/*=true*/, 
  bool Vflip/*=false*/, bool Hflip/*=false*/)
{
  draw(color, prefill, Vflip, Hflip);
}

