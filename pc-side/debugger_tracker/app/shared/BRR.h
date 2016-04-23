#pragma once

#include "SDL.h"
#include "utility.h"
#include "gme/Spc_Dsp_Register_Map_Interface.h"
#include "BaseD.h"
#include "nfd.h"

struct BRR
{
  BRR();
  enum BRR_TYPE {
    CLICKED_ON_LOOP_ONLY=0,
    LOOP_SAMPLE,
    PLAIN_SAMPLE,
    NOT_A_SAMPLE
  };

  static int write_plain_brr_to_file(BRR *brr);
  static int write_brrp_to_file(BRR *brr);
  static int write_brri_to_file(BRR *brr);
  static int write_loop_info_to_file(BRR *brr, SDL_RWops *file);

  static const char BRRP_MAGIC_STR[];
  static const char BRRI_MAGIC_STR[];
  static const char BRR_FILE_EXTENSION[];
  static const char BRRP_FILE_EXTENSION[];
  static const char BRRI_FILE_EXTENSION[];

  bool is_looped_sample=false;
  bool is_loop_external=false;
  Uint8 one_solo=0x0;
  Uint8 corresponding_voice=0x0;
  Uint8 srcn_solo=0x0;
  Uint16 srcn[MAX_VOICES];  // current voices' SRCN addresses
  Uint16 brr_start,brr_end; // for downloading BRR samples
  Uint16 brr_loop_start,brr_loop_end;
  Uint8 lowest_srcn_index=0x0;  // indexes into report::src[]
  Uint8 lowest_loop_index=0x0;
  int check_brr(Uint16 *address);
  // temporarily OUT-OF-ORDER
  //void play_sample(Instrument_Window *instr_window);
  void solo_sample();
};