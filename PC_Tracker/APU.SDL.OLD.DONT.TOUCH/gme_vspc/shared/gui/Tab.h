#pragma once
#include "gui/Clickable_Rect_Id.h"
#include <string>
struct Tab : public Clickable_Rect_Id
{
  Tab();
  Tab(int x, int y, int pad_size, std::string str, 
    int (*action)(void *data, int id)=NULL, void *data=NULL);
  Tab(int x, int y, int pad_w_size, int pad_h_size, std::string str,
    int (*action)(void *data, int id)=NULL, void *data=NULL);
  Tab(int pad_w_size, int pad_h_size, std::string str,
    int (*action)(void *data, int id)=NULL, void *data=NULL);
  void draw(SDL_Surface *screen=Render_Context::screen, bool active=false);
  int horiz_pixel_length();
  bool check_mouse_and_execute(int x, int y, void *newdata=NULL);
  
  std::string str;
  int pad_w_size, pad_h_size;
};

/*
 ------
| TEXT |
 ------
*/