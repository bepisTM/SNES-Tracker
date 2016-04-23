#pragma once
#include "BaseD.h"
#include "gme/Spc_Dsp_Register_Map_Interface.h"
#include "sdl_dblclick.h"
#include "Colors.h"
#include "sdlfont.h"
#include "Experience.h"
#include "gui/Clickable_Text.h"
#include "gui/cursor.h"
#include "utility.h"
#include "ADSR.h"
#include "gui/Expanding_List.h"
#include "Midi.h"

struct Instr_Tab: public BaseD,
public Experience
{
  int midi_callback(double deltatime, jdkmidi::MIDIMessage *m, void *userData);
  Uint32 mytime;
  bool started=false;
  Instr_Tab(int x, int y);
  void activate();
  void deactivate();
  void run();
  void draw();
  void one_time_draw();
  int receive_event(SDL_Event &ev);

  void play_pitch(int p, bool abs=false);
  void pause_spc();
  void restore_spc(bool resume=true);

  void set_voice(unsigned char v);
  void inc_voice();
  void dec_voice();
  void inc_octave();
  void dec_octave();

  void keyoff_current_voice();

  struct Start_Stop
  {
    Start_Stop() : startc("Start", 10, 10), stopc("Stop ", 10, 10) {}
    Clickable_Text startc, stopc;
    bool is_started=false;
  } start_stop;
  

  struct AdjustableUD
  {
    AdjustableUD(const char *label) : up_arrow("\x5c"), down_arrow("\x5c"), label(label) {}
    Clickable_Text up_arrow,down_arrow;
    Clickable_Text label;
    uint8_t n=4;
    int n_x,n_y;
  };
  struct AdjustableLR
  {
    AdjustableLR(const char *label) : right_arrow("\x5d"), left_arrow("\x5d"), label(label) {}
    Clickable_Text right_arrow,left_arrow;
    Clickable_Text label;
    uint8_t n=0;
    int n_x,n_y;
  };
  // should go into a voice class but...
  Uint8 adsr1, adsr2;

  AdjustableUD octave;
  AdjustableLR voice;
  
  int scancode=0; // there's a reason for saving the scancode.. not sure if it's purposed anymore
  
  //track_info_t track_info_backup, track_info_backup2; // cause of pass by reference

  struct
  {
    int x,y;

  } adsr, attack, decay, sustain_level, sustain_release;  

  ADSR::Context_Menus adsr_context_menus;

  enum modes 
  { 
    MODE_NAV=0,
  };
  int mode=MODE_NAV;
  enum submodes
  {
    NONE=0,
  };
  int submode=NONE;
  
  bool is_first_run=true;
  // midi
  Uint8 last_note_on=0;

  int start_x,start_y;
};

