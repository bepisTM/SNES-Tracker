#pragma once

#include "gui/Window.h"
#include "Mem_Tab.h"
#include "Dsp_Tab.h"
#include "Instr_Tab.h"

// Some of these functions might need a BaseD wrapper
// going to have to look at exp Experience* 

// Tabs need to construct with Main_Window's render objects

class Main_Window : public Window
{
  Main_Window(int &argc, char **argv);

  void update_window_title();

  void switch_mode(int mode);
  int switch_to_memory(void *data);
  int switch_to_dsp(void *data);
  int switch_to_instrument(void *data);

  void toggle_pause();
  void if_exp_is_instr_window_then_restore_spc();

  Experience *cur_tab_exp;

  Menu_Bar menu_bar;
  Mem_Tab mem_tab;
  Dsp_Tab dsp_window;
  Instr_Tab instr_window;

  enum Tab
  {
    NONE=0,
    MEM,
    DSP_MAP,
    INSTRUMENT,
  };

  Tab active_tab() { return currently_open_tab; }

  Tab currently_open_tab = Tab::MEM;
  Tab last_open_tab = Tab::NONE;
  // this will be used ^ in the event processing, drawing, etc.

  struct Tabs
  {
    SDL_Rect rect;

    enum {
      mem=0,
      dsp,
      instr,
      num_tabs
    };
    void preload(int x, int y);
    Tabs() : tabs[mem](3,3, "Mem", BaseD::switch_to_memory, NULL, true),
      tabs[dsp](3,3, "DSP", BaseD::switch_to_dsp, NULL),
      tabs[instr](3,3, "INSTR", BaseD::switch_to_instrument, NULL)
    {

    }
    bool check_mouse_and_execute(int x, int y)
    {
      for (int i=0; i < num_tabs; i++)
      {
        if(tabs[i].check_mouse_and_execute(x,y))
        {
          
        }
      }
      if (mem.check_mouse_and_execute(x,y)) 
      {
        // mem.active = true;
        // dsp.active = false;
        // instr.active = false;
        return true;
      }
      if (dsp.check_mouse_and_execute(x,y)) 
      {
        // mem.active = false;
        // dsp.active = true;
        // instr.active = false;
        return true;
      }
      if (instr.check_mouse_and_execute(x,y))
      {
        // mem.active = false;
        // dsp.active = false;
        // instr.active = true;
        return true;
      }
      return false;
    }
    Tab tabs[num_tabs]; //mem, dsp, instr;
    void draw ();
    static int memory(void *data);
    static int DSP(void *data);
    static int Instrument(void *data);

    //int logged_grand_mode=BaseD::GrandMode::MAIN;
  } tabs;

private:
  void check_quit(SDL_Event &ev);
};
