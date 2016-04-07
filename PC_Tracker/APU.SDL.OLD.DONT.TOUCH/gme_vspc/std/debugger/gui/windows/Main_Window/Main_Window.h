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

  // This I might need to implement (came from BaseD)
  //Experience *exp;

  Mem_Tab main_window;
  Dsp_Tab dsp_window;
  Instr_Tab instr_window;
  Menu_Bar menu_bar;

  enum Tab
  {
    MEM=0,
    DSP_MAP,
    INSTRUMENT,
  };

  Tab active_tab() { return currently_open_tab; }

  Tab currently_open_tab = Tab::MEM;
  // this will be used ^ in the event processing, drawing, etc.

private:
  void check_quit(SDL_Event &ev);
};
