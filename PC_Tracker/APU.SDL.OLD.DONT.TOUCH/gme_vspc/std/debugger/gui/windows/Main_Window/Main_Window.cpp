#include "Main_Window.h"

Main_Window::Main_Window(int width, int height, const char *title) :
Window(width, height, title)
{
  cur_tab_exp = (Experience *)&mem_tab;
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

void Main_Window::Tabs::preload(int x, int y)
{
  // init Tabs
  mem.rect.x = x;
  mem.rect.y = y; // + h + CHAR_HEIGHT*2;
  //
  dsp.rect.x = mem.rect.x + mem.horiz_pixel_length() + CHAR_WIDTH;
  dsp.rect.y = mem.rect.y;
  //
  instr.rect.x = dsp.rect.x + dsp.horiz_pixel_length() + CHAR_WIDTH;
  instr.rect.y = mem.rect.y;

  rect = {mem.rect.x, mem.rect.y, instr.rect.x + instr.rect.w, CHAR_HEIGHT};
}

void Main_Window::Tabs::draw()
{
  // tmpfix
  // if (BaseD::grand_mode != logged_grand_mode)
  // {
  //   logged_grand_mode = BaseD::grand_mode;

  //   if (BaseD::grand_mode == BaseD::GrandMode::MAIN)
  //   {
  //     mem.active = true;
  //     dsp.active = false;
  //     instr.active = false;
  //   }
  //   else if (BaseD::grand_mode == BaseD::GrandMode::DSP_MAP)
  //   {
  //     mem.active = false;
  //     dsp.active = true;
  //     instr.active = false;
  //   }
  //   else if (BaseD::grand_mode == BaseD::GrandMode::INSTRUMENT)
  //   {
  //     mem.active = false;
  //     dsp.active = false;
  //     instr.active = true;
  //   }    
  // }
  mem.draw();
  dsp.draw();
  instr.draw();
}

void Main_Window::one_time_draw()
{
  tabs.preload(menu_bar.context_menus.x, 
    menu_bar.context_menus.y + menu_bar.context_menus.h + CHAR_HEIGHT*2);
  cur_tab_exp->one_time_draw();
}

void Main_Window::run()
{
  cur_tab_exp->run();
}

void Main_Window::draw()
{
  tabs.draw();
  cur_tab_exp->draw();
  menu_bar.draw();
}

int Main_Window::receive_event(SDL_Event &ev)
{
  // Do global stuff here
  if (ev.type == SDL_MOUSEBUTTONDOWN)
  {
    if (!BaseD::player->has_no_song)
    {
      bool r = tabs.check_mouse_and_execute(ev.button.x, ev.button.y);
      if (r) return r;
    }
  }

  // then :
  cur_tab_exp->receive_event(ev);
}

// dunno if I'll need this
void Main_Window::activate()
{

}
void Main_Window::deactivate()
{

}

void Main_Window::check_quit(SDL_Event &ev)
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





