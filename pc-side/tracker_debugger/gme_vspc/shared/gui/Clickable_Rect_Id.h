#pragma once
#include "sdlfont.h"
#include "Render_Context.h"
#include "Render_Collection.h"

struct Clickable_Rect_Id : public Render_Context
{
  Clickable_Rect_Id(int (*action)(void *data, int id)=NULL, void *data=NULL);
  Clickable_Rect_Id();
  Clickable_Rect_Id(int x, int y, int w, int h, int (*action)(void *data, int id)=NULL, void *data=NULL);
  void set_rect(int x, int y, int w, int h);
  bool check_mouse_and_execute(int x, int y, void *newdata=NULL);
  SDL_Rect rect;
  void do_thing(void *newdata=NULL);
  int (*action)(void* data, int id);
  

  int id;
private:
	static int id_count;
  void *data;

  // should go into an impl-specific class
  //Render_Collection *rc;

};