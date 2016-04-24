#include "Main_Window.h"
#include "stub.h"

static int switch_tab(void *winp, int ntab)
{
  Main_Window *mw = (Main_Window *)winp;
  mw->switch_tab(ntab);
}


Main_Window::Main_Window(int width, int height, const char *title) :
Window(width, height, title),
tabs(menu_bar.context_menus.x,
  menu_bar.context_menus.y + menu_bar.context_menus.h + CHAR_HEIGHT*2,
  rc,
  ::switch_tab),
dsp_tab(10, tabs.rect.y + tabs.rect.h + TILE_HEIGHT*5),
instr_tab(tabs.rect.x, tabs.rect.y + tabs.rect.h + (4*TILE_HEIGHT))
{
  exp = (Experience *)&mem_tab;
}

// BaseD::menu_bar->tabs.rect.y + BaseD::menu_bar->tabs.rect.h + TILE_HEIGHT*5

// update window title with track info
void Main_Window::update_window_title()
{
  STUB("implement appropriately");
  // long seconds = player->track_info().length / 1000;
  // const char* game = player->track_info().game;
  // if ( !*game )
  // {
  //   // extract filename
  //   game = strrchr( path, '\\' ); // DOS
  //   if ( !game )
  //     game = strrchr( path, '/' ); // UNIX
  //   if ( !game )
  //     game = path;
  //   else
  //     game++; // skip path separator
  // }

  // char title [512];
  // sprintf( title, "%s: %d/%d %s (%ld:%02ld)",
  //     game, g_cur_entry+1, g_cfg.num_files, player->track_info().song,
  //     seconds / 60, seconds % 60 );
  // SDL_SetWindowTitle(sdlWindow, title);
}

void Main_Window::Tabs::preload(int x, int y)
{
  int i=0;
  // init Tabs
  tabs[i].rect.x = x;
  tabs[i++].rect.y = y;
  //
  tabs[i].rect.x = tabs[i-1].rect.x + tabs[i-1].horiz_pixel_length() + CHAR_WIDTH;
  tabs[i++].rect.y = y;
  //
  tabs[i].rect.x = tabs[i-1].rect.x + tabs[i-1].horiz_pixel_length() + CHAR_WIDTH;
  tabs[i++].rect.y = y;

  rect = {tabs[0].rect.x, tabs[0].rect.y, tabs[num_tabs-1].rect.x + tabs[num_tabs-1].rect.w, CHAR_HEIGHT};
}

void Main_Window::Tabs::draw()
{
  for (int i=0; i < num_tabs; i++)
  {
    tabs[i].draw(rc.screen, i == which_active);
  }
}

void Main_Window::one_time_draw()
{
  exp->one_time_draw();
}

void Main_Window::run()
{
  exp->run();
}

void Main_Window::draw()
{
  tabs.draw();
  exp->draw();
  menu_bar.draw(rc.screen);
}

int Main_Window::receive_event(SDL_Event &ev)
{
  menu_bar.receive_event(ev);

  // Do global stuff here
  switch (ev.type)
  {
  case SDL_MOUSEBUTTONDOWN:
    {
      if (!BaseD::player->has_no_song)
      {
        bool r = tabs.check_mouse_and_execute(ev.button.x, ev.button.y);
        if (r) return r;
      }
      break;
    }

  case SDL_KEYDOWN:
    {
      int scancode = ev.key.keysym.sym;
      //bool is_shift_pressed=false;
      switch (scancode)
      {
      case SDLK_SPACE:
        toggle_pause();
      case SDLK_SLASH:
        cycle_tabs();
        break;
      default:break;
      }
      break;
    }

    default:break;
  }


  // then :
  exp->receive_event(ev);
}

void Main_Window::cycle_tabs()
{
  STUBBED("Main_Window::cycle_tabs");
}
// dunno if I'll need this
void Main_Window::activate()
{
  STUBBED("Main_Window::activate");
}
void Main_Window::deactivate()
{
  STUBBED("Main_Window::deactivate");
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
    BaseD::quitting = true;
    break;

    case SDL_KEYDOWN:
    switch (ev.key.keysym.sym)
    {
      default:break;
    }
    break;

    default:break;
  }
}

int Main_Window::switch_tab(int ntab)
{
  if (tabs.which_active == ntab)
    return;
  tabs.which_active = ntab;
  rc.clear_screen();

  if (ntab == Tabs::mem)
  {
    if_exp_is_instr_window_then_restore_spc();
    exp = (Experience*)&mem_tab;
    one_time_draw();
  }
  else if (ntab == Tabs::dsp)
  {
    exp = (Experience*)&dsp_tab;
  }
  else if (ntab == Tabs::instr)
  {
    exp = (Experience*)&instr_tab;
    instr_tab.one_time_draw();
  }
}

// int Main_Window::Tabs::switch_to_memory(void *data)
// {
//   (Main_Window *)data->switch_tab(Tabs::mem);
//   return 0;
// }
// int Main_Window::Tabs::switch_to_dsp(void *data)
// {
//   (Main_Window *)data->switch_tab(Tabs::dsp);
//   return 0;
// }
// int Main_Window::Tabs::switch_to_instrument(void *data)
// {
//   (Main_Window *)data->switch_tab(Tabs::instr);
//   return 0;
// }

void Main_Window::toggle_pause()
{
  // this means (if the player has finished playing its last song...)
  // the player stops, but if the user tries to resume with space_bar or play command
  // this will restart from beginning of playlist
  if (BaseD::g_cur_entry >= BaseD::g_cfg.num_files)
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
  if (exp == (Experience*)&instr_tab)
  {
    instr_tab.restore_spc(false); // restore SPC but don't necessarily resume playing
  }
}




