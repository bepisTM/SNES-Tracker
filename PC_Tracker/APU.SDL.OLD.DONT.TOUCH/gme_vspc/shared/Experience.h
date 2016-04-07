#pragma once
#include "SDL.h"
struct Experience
{
  virtual void run()=0;
  virtual void one_time_draw() {}
  virtual void draw()=0;
  virtual int receive_event(SDL_Event &ev)=0;

  virtual void activate()=0;
  virtual void deactivate()=0;
};