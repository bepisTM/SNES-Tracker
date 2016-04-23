#include "sdl.h"
#include "gme/player/Music_Player.h"
#include "Debugger.h"
#include "Midi_Context.h"
#include "File_System.h"
#include "File_System_Context.h"
#include "App_Settings_Context.h"
#include "Audio.h"
#include "gui/Cursors.h"

class App
{
public:
  App(int &argc, char **argv, int samplerate=44100);
  ~App();
  void run();
  
  App_Settings *app_settings;
  
  Audio *audio;
  File_System *file_system;

private:
  int init_sdl();
};

class MidiApp
{
public:
  Midi_App()

private:
  App app;
  Midi midi;
};

class Spc_App
{
private:
  Midi_App midi_app;
  Music_Player *player;
};