#include "Main_Window.h"

Main_Window::Main_Window(int &argc, char **argv) :
Window(SCREEN_WIDTH, SCREEN_HEIGHT, APP_NAME_VERSION)
{
  int res;
  static struct option long_options[] = {
    {"nosound", 0, 0, 0},
    {"novideo", 0, 0, 1},
    {"update_in_callback", 0, 0, 2},
    {"echo", 0, 0, 3},
    {"interpolation", 0, 0, 4},
    {"savemask", 0, 0, 5},
    {"default_time", 1, 0, 6},
    {"ignore_tag_time", 0, 0, 7},
    {"extra_time", 1, 0, 8},
    {"yield", 0, 0, 9},
    {"auto_write_mask", 0, 0, 10},
    {"status_line", 0, 0, 11},
    {"help", 0, 0, 'h'},
    {"apply_mask_block", 0, 0, 12},
    {"apply_mask_byte", 0, 0, 13},
    {"filler", 1, 0, 14},
    {0,0,0,0}
  };

  while ((res=getopt_long(argc, argv, "h",
        long_options, NULL))!=-1)
  {
    switch(res)
    {
      case 0:
        g_cfg.nosound = 1;
        break;
      case 1:
        g_cfg.novideo = 2;
        break;
      case 2:
        g_cfg.update_in_callback = 1;
        break;
      case 4:
        //spc_config.is_interpolation = 1;
        break;
      case 3:
        //spc_config.is_echo = 1;
        break;
      case 5:
        g_cfg.autowritemask = 1;
        break;
      case 6:
        g_cfg.defaultsongtime = atoi(optarg);
        break;
      case 7:
        g_cfg.ignoretagtime = 1;
        break;
      case 8:
        g_cfg.extratime = atoi(optarg);
        break;
      case 9:
        g_cfg.nice = 1;
        break;
      case 10:
        g_cfg.autowritemask = 1;
        break;
      case 11:
        g_cfg.statusline = 1;
        break;
      case 12:
        g_cfg.apply_block = 1;
        break;
      case 14:
        g_cfg.filler = strtol(optarg, NULL, 0);
        break;
      case 'h':
        printf("Usage: ./vspcplay [options] files...\n");
        printf("\n");
        printf("Valid options:\n");
        printf(" -h, --help     Print help\n");
        printf(" --nosound      Dont output sound\n");
        printf(" --novideo      Dont open video window\n");
        printf(" --update_in_callback   Update spc sound buffer inside\n");
        printf("                        sdl audio callback\n");
        printf(" --interpolation  Use sound interpolatoin\n");
        printf(" --echo           Enable echo\n");
        printf(" --auto_write_mask   Write mask file automatically when a\n");
        printf("                     tune ends due to playtime from tag or\n");
        printf("                     default play time.\n");
        printf(" --default_time t    Set the default play time in seconds\n");
        printf("                     for when there is not id666 tag. (default: %d\n", DEFAULT_SONGTIME);
        printf(" --ignore_tag_time   Ignore the time from the id666 tag and\n");
        printf("                     use default time\n");
        printf(" --extra_time t      Set the number of extra seconds to play (relative to\n");
        printf("                     the tag time or default time).\n");
        printf(" --nice              Try to use less cpu for graphics\n");
        printf(" --status_line       Enable a text mode status line\n");
        printf("\n!!! Careful with those!, they can ruin your sets so backup first!!!\n");
        printf(" --apply_mask_block  Apply the mask to the file (replace unreport::used blocks(256 bytes) with a pattern)\n");
        printf(" --filler val        Set the pattern byte value. Use with the option above. Default 0\n");
        printf("\n");
        printf("The mask will be applied when the tune ends due to playtime from tag\n");
        printf("or default playtime.\n");
        exit(0);
        break;
    }
  }

  g_cfg.num_files = argc-optind;
  g_cfg.playlist = &argv[optind];
}

// update window title with track info
void Main_Window::update_window_title()
{

  long seconds = player->track_info().length / 1000;
  const char* game = player->track_info().game;
  if ( !*game )
  {
    // extract filename
    game = strrchr( path, '\\' ); // DOS
    if ( !game )
      game = strrchr( path, '/' ); // UNIX
    if ( !game )
      game = path;
    else
      game++; // skip path separator
  }
  
  char title [512];
  sprintf( title, "%s: %d/%d %s (%ld:%02ld)",
      game, g_cur_entry+1, g_cfg.num_files, player->track_info().song,
      seconds / 60, seconds % 60 );
  SDL_SetWindowTitle(sdlWindow, title);
}

void Mem_Tab::check_quit(SDL_Event &ev)
{
  switch (ev.type)
  {
    case SDL_QUIT:
    /*if (!g_cfg.nosound) {
      SDL_PauseAudioDevice(Audio_Context::audio->devices.id, 1);
    }*/
    printf ("penis4\n");
    quitting = true;
    break;

    case SDL_KEYDOWN:
    if (ev.key.keysym.sym == SDLK_ESCAPE)
    {
      if (!locked() && mode != MODE_EDIT_APU_PORT)
      {
        fprintf(stderr, "penis88\n");
        /*if (!g_cfg.nosound) {
          SDL_PauseAudioDevice(Audio_Context::audio->devices.id, 1);
        }*/
        quitting = true;
      }
      
    }
  }
}

void Main_Window::switch_mode(int nmode)
{
  if (mode == nmode)
    return;
  mode = nmode;
  clear_screen();
  //draw_menu_bar();

  // If we switched from instrument window, need to re-enable regular spc playback
  

  if (nmode == GrandMode::MAIN)
  {
    if_exp_is_instr_window_then_restore_spc();
    if (main_window)
      exp = (Experience*)main_window;
    else 
    {
      fprintf(stderr, "NO MAIN WINDOW!?!\n");
      exit(2);
    }
    main_window->one_time_draw();
  }
  else if (nmode == GrandMode::DSP_MAP)
  {
    if (dsp_window)
      exp = (Experience*)dsp_window;
    else 
    {
      fprintf(stderr, "NO DSPWINDOW!?!\n");
      exit(2);
    }
  }
  else if (nmode == GrandMode::INSTRUMENT)
  {
    if (instr_window)
      exp = (Experience*)instr_window;
    else
    {
      fprintf(stderr, "NO INSTRUMENT_WINDOW!?!\n");
      exit(2);
    }
    instr_window->one_time_draw();
  }
}

int Main_Window::switch_to_memory(void *data)
{
  (Main_Window *)data->switch_mode(Tab::MEM);
  return 0;
}
int Main_Window::switch_to_dsp(void *data)
{
  (Main_Window *)data->switch_mode(Tab::DSP_MAP);
  return 0;
}
int Main_Window::switch_to_instrument(void *data)
{
  (Main_Window *)data->switch_mode(Tab::INSTRUMENT);
  return 0;
}

void Main_Window::toggle_pause()
{
  // this means (if the player has finished playing its last song...)
  // the player stops, but if the user tries to resume with space_bar or play command
  // this will restart from beginning of playlist
  if (g_cur_entry>=g_cfg.num_files)
  {
    restart_track();
  }
  else 
  {
    if_exp_is_instr_window_then_restore_spc();
    player->toggle_pause();
  }
}

void Main_Window::if_exp_is_instr_window_then_restore_spc()
{
  if (exp == (Experience*)instr_window)
  {
    instr_window->restore_spc(false); // restore SPC but don't necessarily resume playing
  }
}





