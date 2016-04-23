#pragma once

#include <map>
#include "RtMidi.h"
#include "App_Settings_Context.h"

#include "jdkmidi/world.h"
#include "jdkmidi/midi.h"
#include "jdkmidi/msg.h"
#include "jdkmidi/sysex.h"
#include "jdkmidi/parser.h"

struct Midi : public App_Settings_Context
{
  typedef int (*MidiCallback)( double timeStamp, jdkmidi::MIDIMessage *m, void *userData);
  //typedef int (*MidiCallback)( double timeStamp, std::vector<unsigned char> *message, void *userData);

  Midi();
  ~Midi();

  void PrintSysEx( FILE *f, jdkmidi::MIDISystemExclusive *ex );
  void PrintMsg( FILE *f, jdkmidi::MIDIMessage *m );

  int internal_callback(double &deltatime, std::vector< unsigned char > *message);

  /* RtMidi Stuffz */
  std::map<int, std::string> apiMap;
  std::vector< RtMidi::Api > apis;
  std::vector<std::string> available_devices;
  RtMidiIn  in;
  bool is_available=true;

  void setCallback(MidiCallback callback, void *userData = 0 );
  MidiCallback callback = NULL;
  void *userData = NULL;
  //RtMidiOut *midiout = 0;
  //Uint8 last_note_on=0;

  // jdkmidi stuffz
  jdkmidi::MIDIParser parser;
  jdkmidi::MIDIMessage msg;
};