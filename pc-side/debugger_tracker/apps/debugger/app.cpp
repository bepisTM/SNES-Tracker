#include "app.h"
#include "DEBUGLOG.h"
#include "Audio_Context.h"

#define assign_contexts(nameless) \
{\
  File_System_Context::file_system = file_system;\
  App_Settings_Context::app_settings = app_settings;\
  Audio_Context::audio = audio;\
}
App::App()
{
  file_system = new File_System;
  app_settings = new App_Settings(file_system);
  audio = new Audio;
  assign_contexts();
}
#undef assign_contexts


void App::run()
{
}

App::~App()
{
  DEBUGLOG("~App;");

  delete app_settings;
  delete audio;
  delete file_system;
}

// - - -- - - - - -- -
static int create_midi(void *vapp)
{
  App *app = (App *)vapp;
  app->midi = new Midi;
  Midi_Context::midi = app->midi;
  return 0;
}

Spc_App::Spc_App(int samplerate/*=44100*/)
{
  player = new Music_Player;
  Player_Context::player = player;
  handle_error(player->init(samplerate, app_settings->vars.audio_out_dev));

  // implementation-specific detail should be extracted
  SDL_Thread *thread = SDL_CreateThread(create_midi, "create_midi", this);
  SDL_DetachThread(thread);
}

Spc_App::~Spc_App()
{
  delete player;
}

