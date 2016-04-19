#pragma once

#include "gui/Window.h"
#include "Mem_Tab.h"
#include "Dsp_Tab.h"
#include "Instr_Tab.h"
#include "Menu_Bar.h"

// Some of these functions might need a BaseD wrapper
// going to have to look at exp Experience* 

// Tabs need to construct with Main_Window's render objects

class Main_Window : public Window, public Player_Context
{
public:
  Main_Window(int &argc, char **argv);

  void update_window_title();

  int switch_tab(void *inst, int ntab);

  void toggle_pause();
  void if_exp_is_instr_window_then_restore_spc();

  Experience *exp;

  Menu_Bar menu_bar;
  Mem_Tab mem_tab;
  Dsp_Tab dsp_tab;
  Instr_Tab instr_tab;

  struct Tabs
  {
    SDL_Rect rect;

    enum {
      mem=0,
      dsp,
      instr,
      num_tabs
    };
    int which_active = tabs[mem].id;
    int which_last = tabs[mem].id;
    void preload(int x, int y);

    Tabs(int (*callback)(void *data, int id)=NULL, void *window=NULL) :
      tabs{
        Tab(3,3, "Mem", callback, window),
        Tab(3,3, "DSP", callback, window),
        Tab(3,3, "INSTR", callback, window)}
    {

    }
    bool check_mouse_and_execute(int x, int y)
    {
      for (int i=0; i < num_tabs; i++)
      {
        if(tabs[i].check_mouse_and_execute(x,y))
        {
          which_active = tabs[i].id;
          return true;
        }
      }
      return false;
    }
    Tab tabs[num_tabs];

    void draw ();
    void run() {}
    // static int memory(void *data);
    // static int DSP(void *data);
    // static int Instrument(void *data);
  } tabs;

private:
  void check_quit(SDL_Event &ev);
  void cycle_tabs();
};
