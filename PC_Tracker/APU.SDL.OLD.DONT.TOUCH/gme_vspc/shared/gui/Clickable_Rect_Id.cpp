#include "Clickable_Rect_Id.h"
#include "utility.h"
#include <assert.h>

int Clickable_Rect_Id::id_count = 0;

Clickable_Rect_Id::Clickable_Rect_Id(int (*action)(void *data, int id)/*=NULL*/, void *data/*=NULL*/) : 
action(action),
data(data),
id(id_count++)
{

}

Clickable_Rect_Id::Clickable_Rect_Id(int x, int y, int w, int h, 
  int (*action)(void *data, int id)/*=NULL*/, void *data/*=NULL*/) : 
rect({x,y,w,h}), 
action(action),
data(data),
id(id_count++)
{

}

bool Clickable_Rect_Id::check_mouse_and_execute(int x, int y, void *newdata/*=NULL*/)
{
  if (Utility::coord_is_in_rect(x,y, &rect))
  {
    do_thing(newdata);
    return true;
  }
  return false;
}

void Clickable_Rect_Id::set_rect(int x, int y, int w, int h)
{
  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;
}

void Clickable_Rect_Id::do_thing(void *newdata/*=NULL*/)
{
  assert(action);
  if (!newdata)
    action(data, id);
  else action(newdata, id);
}