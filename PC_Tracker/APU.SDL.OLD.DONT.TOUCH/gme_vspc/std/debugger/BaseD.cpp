#include "BaseD.h"
/*Music_Player *BaseD::player;
SDL_Surface *BaseD::screen;
uint8_t *BaseD::IAPURAM;*/
#include "Main_Window.h"
#include "Menu_Bar.h"
#include "File_System_Context.h"
#include "stub.h"
#include <getopt.h>
char BaseD::tmpbuf[500];

// this doesn't belong in BaseD
bool BaseD::Profile::is_profiling=false;
BaseD::Profile * BaseD::tmp_profile=NULL;

My_Nfd BaseD::nfd;

BaseD::Cfg BaseD::g_cfg;// = { 0,0,0,0,0,0,DEFAULT_SONGTIME,0,0,0,0,0,NULL };

bool BaseD::is_first_run=true;
int BaseD::g_paused = 0;
uint8_t * BaseD::IAPURAM=NULL;
bool BaseD::quitting=false;
unsigned char BaseD::packed_mask[32];

int BaseD::g_cur_entry= 0;
bool BaseD::paused;

int BaseD::song_time;
track_info_t BaseD::tag;
char * BaseD::g_real_filename=NULL;
char BaseD::now_playing[1024];
//bool BaseD::is_onetime_draw_necessary=false;


//Experience * BaseD::exp=NULL;

//Menu_Bar * BaseD::menu_bar=NULL;
// Options_Window * BaseD::options_window=NULL;
// Spc_Export_Window * BaseD::spc_export_window=NULL;

Cursors * BaseD::cursors=NULL;

const char * BaseD::path=NULL;
Voice_Control BaseD::voice_control;

uint16_t BaseD::Hack_Spc::pc_backup;
uint16_t *BaseD::Hack_Spc::pc_ptr=NULL;
int BaseD::Hack_Spc::song_time_backup;
bool BaseD::Hack_Spc::is_started=false;

void BaseD::Hack_Spc::pause_spc()
{
  player->pause(1, true, false);
  // backup_pc()
  pc_ptr = (uint16_t*)&IAPURAM[(int)player->spc_emu()->pc()];
  pc_backup = *pc_ptr;

  song_time_backup = BaseD::song_time;
  BaseD::song_time = 10000;
  //player->ignore_silence();
  player->emu()->set_fade(1000*10000, 8000);


  // write with never-ending loop
  
  // overwrite_pc_with_endless_loop()
  *pc_ptr = ENDLESS_LOOP_OPCODE;

  player->pause(0);

  player->spc_write_dsp(dsp_reg::koff, 0xff);
  SDL_Delay(100);
  player->spc_write_dsp(dsp_reg::koff, 0x00);
  is_started=true;
}

void BaseD::Hack_Spc::restore_spc(bool resume/*=true*/)
{
  // restore_pc()
  //uint16_t *pc_ptr = (uint16_t*)&IAPURAM[report::last_pc];
  if (!pc_ptr || !is_started) return;
  player->pause(1, true, false);
  *pc_ptr = pc_backup;
  if (resume) player->pause(0);
  pc_ptr = NULL;
  is_started=false;
  //BaseD::song_time = song_time_backup;
  //track_info_backup = track_info_backup2;
}

BaseD::Profile::Profile(const char* spc_filename)
{
  is_profiling = true;
  old_gain_db = BaseD::player->gain_db;
  BaseD::player->pause(1, true, false);
  BaseD::reload();
  BaseD::player->pause(0, false, false);
  BaseD::player->pause(1, false, false);
  //BaseD::player->restart_track();
  // Set Volume to 0
  player->set_gain_db(Music_Player::min_gain_db, true);
  // get pointer to spc_file_t
  // open the SPC File
  //DEBUGLOG("spc file path = %s\n", BaseD::g_cfg.playlist[BaseD::g_cur_entry]);
  //const char *spc_filename = BaseD::g_cfg.playlist[BaseD::g_cur_entry];
  // need to open a file
  SDL_RWops *orig_spc_file = SDL_RWFromFile(spc_filename, "rb");
  if (orig_spc_file == NULL)
  {
    sprintf(BaseD::tmpbuf, "Warning: Unable to open file %s!\n %s", spc_filename, SDL_GetError() );
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                   "Could not open FILE!",
                   BaseD::tmpbuf,
                   NULL);
    //return -1;
    is_profiling=false;
    delete this;
  }

  if (SDL_RWread(orig_spc_file, orig_spc_state, Snes_Spc::spc_file_size, 1) == 0)
  {
    sprintf(BaseD::tmpbuf, "Warning: Unable to read file %s!\n %s", spc_filename, SDL_GetError() );
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                   "Could not read file!",
                   BaseD::tmpbuf,
                   NULL);
    SDL_RWclose(orig_spc_file);
    //return -1;
    is_profiling=false;
    delete this;
  }
  else SDL_RWclose(orig_spc_file);
}

void BaseD::Profile::process()
{
  //BaseD::player->pause(0, false); // no fade
  /* Skip several seconds */
  BaseD::player->spc_emu()->skip(120 * Snes_Spc::sample_rate * 2);

  /*elapsed_seconds = (int((BaseD::player->emu()->tell()/1000)));
  if (elapsed_seconds == seconds_covered+1)
  {
    //BaseD::player->pause(1, false, false);
    DEBUGLOG("seconds elapsed: %d\n", elapsed_seconds);
    seconds_covered = elapsed_seconds;
  }*/
  seconds_covered++;
  //DEBUGLOG("f\n");
  if (seconds_covered == 1)
  {
    BaseD::player->set_gain_db(old_gain_db);
    BaseD::Profile::is_profiling=false;
    delete this;
  }
}

int BaseD::Clickable::toggle_echo(void *nada)
{
  player->spc_emu()->toggle_echo();
  return 0;
}

int BaseD::Clickable::inc_tempo(void *nada)
{
  player->inc_tempo();
  return 0;
}
int BaseD::Clickable::dec_tempo(void *nada)
{
  player->dec_tempo();
  return 0;
}

#ifdef _WIN32
#define UNRAR_TOOLNAME "unrar.exe"
#define DEC7Z_TOOLNAME "7zDec.exe"
#else
#define UNRAR_TOOLNAME "unrar"
#define DEC7Z_TOOLNAME "7zDec"
#endif

namespace fs = ::boost::filesystem;
// return the filenames of all files that have the specified extension
// in the specified directory and all subdirectories
void get_file_list_ext(const fs::path& root, const std::string& ext, std::vector<fs::path>& ret)
{
    if(!fs::exists(root) || !fs::is_directory(root)) return;

    DEBUGLOG("!@#!@# ");
    fs::recursive_directory_iterator it(root);
    fs::recursive_directory_iterator endit;

    while(it != endit)
    {
        if(fs::is_regular_file(*it) && it->path().extension() == ext)
        {
          ret.push_back(it->path().filename());
          std::cout << it->path().filename();
        }
        ++it;
    }

}

void BaseD::init_cmdline(int &argc, char **argv)
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

void BaseD::check_paths_and_reload(char **paths/*=g_cfg.playlist*/, 
  int numpaths/*=g_cfg.num_files*/, bool is_drop_event/*=false*/)
{
  struct
  {
    std::string cmd[2] = { UNRAR_TOOLNAME "\" e -y \"", DEC7Z_TOOLNAME "\" e \""};
    unsigned index=0;
    const char * str() { return cmd[index].c_str(); }
  } extract_cmd;
  
  bool rsn_found=false;
  // Check here if path is RSN
  for (size_t i=0; i < numpaths; i++)
  {
    char *path = paths[i];
    char *ext;
    char *name;
    ext = strrchr(path, '.');

    name = strrchr(path, '\\'); // Windows
    if (!name)
      name = strrchr( path, '/' ); // UNIX
  //assert(name);
    if (!name)
      name = path;
    else
    {
      name += 1; // move past '/' character
    }

    if (!strcmp(ext, ".rsn") || !strcmp(ext, ".rar") || !strcmp(ext, ".7z"))
    {
      rsn_found = true; // not actually used
      fprintf(stderr, "rsn || 7z found\n");
      char *mkdir_cmd = (char*) SDL_malloc(sizeof(char) * 
        (strlen(MKDIR_CMD)+
          strlen(File_System_Context::file_system->tmp_path_quoted)+((ext-name+1)+1+5)) );

      char *dir_quoted = (char*) SDL_malloc(sizeof(char) * 
        (strlen(File_System_Context::file_system->tmp_path_quoted)+((ext-name+1)+2+5)) );

      strcpy(mkdir_cmd, MKDIR_CMD);
      char *dirp = mkdir_cmd + strlen(MKDIR_CMD);
      char *sp = mkdir_cmd + strlen(MKDIR_CMD);
      strcpy(sp, File_System_Context::file_system->tmp_path_quoted);
      sp += strlen(File_System_Context::file_system->tmp_path_quoted) - 1;
      // folderp is the game folder inside the tmp dir
      for (char *folderp = name; folderp != ext; folderp++)
      {
        *(sp++) = *folderp;
      }

      *(sp++) = PATH_SEP;
      *(sp++) = '"';
      *sp = 0;
      strcpy (dir_quoted, dirp);
      //strcat(dir_quoted, "/");
      fprintf(stderr, "data_path_quoted = '%s'\n", File_System_Context::file_system->data_path_quoted);
      fprintf(stderr, "tmp_path_quoted = '%s'\n", File_System_Context::file_system->tmp_path_quoted);
      fprintf(stderr, "mkdircmd = '%s'\n", mkdir_cmd);
      fprintf(stderr, "dir = %s\n", dir_quoted);
#ifdef _WIN32
      fflush(NULL);
#endif
      system(mkdir_cmd);

      if (!strcmp(ext, ".rsn") || !strcmp(ext, ".rar"))
      {
        extract_cmd.index = 0;
      }
      else if (!strcmp(ext, ".7z"))
      {
        extract_cmd.index = 1;
      }

      // data_path_quoted + "unrar e " + path + " " + dir_quoted
      char *full_extract_cmd = (char*) SDL_malloc(sizeof(char) * 
        (
          strlen(File_System_Context::file_system->data_path_quoted) +
          strlen(extract_cmd.str()) + 3 + strlen(path) + 2 + strlen(dir_quoted) + 1 +10
        ));
#ifdef _WIN32
      full_extract_cmd[0] = '"';
      strcpy(full_extract_cmd + 1, File_System_Context::file_system->data_path_quoted);
#else
      strcpy(full_extract_cmd, File_System_Context::file_system->data_path_quoted);
#endif
      full_extract_cmd[strlen(full_extract_cmd)-1] = 0;
      strcat(full_extract_cmd, extract_cmd.str());
      strcat(full_extract_cmd, path);
      strcat(full_extract_cmd, "\" ");
      strcat(full_extract_cmd, dir_quoted);
      // int i = strlen(full_extract_cmd);
      // full_extract_cmd[i++] = '"';
      // full_extract_cmd[i++] = 0;
      fprintf(stderr, "full_extract_cmd = '%s'\n", full_extract_cmd);
#ifdef _WIN32
      fflush(NULL);
#endif
      system(full_extract_cmd);
      SDL_free(full_extract_cmd);    

      FILE *fp;
      int status;
      char spc_path[PATH_MAX];

      //int count=0;
      int old_nfd_rsn_spc_path_pos=BaseD::nfd.num_rsn_spc_paths;
      // count how many paths!!
      // ls *.spc
      char *dir_unquoted = &dir_quoted[1];
      dir_quoted[strlen(dir_quoted)-1] = 0;

      typedef std::vector<boost::filesystem::path> vec;
      vec v;
      boost::filesystem::path p(dir_unquoted);
      get_file_list_ext(p, ".spc", v);
      sort(v.begin(), v.end());             // sort, since directory iteration
                                            // is not ordered on some file systems

    
      BaseD::nfd.num_rsn_spc_paths += v.size();

      BaseD::nfd.rsn_spc_paths=(char**)SDL_realloc(
        BaseD::nfd.rsn_spc_paths, 
        sizeof(char*) * (BaseD::nfd.num_rsn_spc_paths+1));

      if (BaseD::nfd.rsn_spc_paths == NULL)
      {
        perror ("realloc");
        break;
      }

      for (vec::const_iterator it(v.begin()), it_end(v.end()); it != it_end; ++it)
      {
        std::cout << "woot" << std::endl;
        std::string spc_path = dir_unquoted + it->string();
        BaseD::nfd.rsn_spc_paths[old_nfd_rsn_spc_path_pos] = (char*) SDL_calloc(spc_path.length()+3, sizeof(char));
        strcpy(BaseD::nfd.rsn_spc_paths[old_nfd_rsn_spc_path_pos], spc_path.c_str());
        old_nfd_rsn_spc_path_pos++; 
      }


      //SDL_free(ls_cmd);
      SDL_free(mkdir_cmd);
      SDL_free(dir_quoted);
    }
    else
    {
      char **tmp;
      if ( (tmp=(char**)SDL_realloc(BaseD::nfd.rsn_spc_paths, sizeof(char*) * (BaseD::nfd.num_rsn_spc_paths+1))) == NULL)
      {
        perror ("realloc");
        break;
      }
      BaseD::nfd.rsn_spc_paths = tmp;
      BaseD::nfd.rsn_spc_paths[BaseD::nfd.num_rsn_spc_paths] = (char*) SDL_calloc(strlen(path)+3, sizeof(char));
      //strcpy(BaseD::nfd.rsn_spc_paths[BaseD::nfd.num_rsn_spc_paths], "\"");
      strcpy(BaseD::nfd.rsn_spc_paths[BaseD::nfd.num_rsn_spc_paths], path);
      //strcat(BaseD::nfd.rsn_spc_paths[BaseD::nfd.num_rsn_spc_paths], "\"");
      //fprintf(stderr, "path = %s\n", BaseD::nfd.rsn_spc_paths[BaseD::nfd.num_rsn_spc_paths]);
      BaseD::nfd.num_rsn_spc_paths++;
    }
  }

  BaseD::reload(BaseD::nfd.rsn_spc_paths,BaseD::nfd.num_rsn_spc_paths);
}
bool BaseD::check_time()
{
  if (player->is_paused())
    return false;
  /* Check if it is time to change tune.
   */   
  if (player->emu()->tell()/1000 >= song_time) 
  {
    fprintf(stderr, "POOP");
    if (g_cfg.autowritemask) {
      write_mask(packed_mask);
      if (g_cfg.apply_block) {
        printf("Applying mask on file %s using $%02X as filler\n", g_cfg.playlist[g_cur_entry], g_cfg.filler);
        applyBlockMask(g_cfg.playlist[g_cur_entry]);
      }
    }
    g_cur_entry++;
    if (g_cur_entry>=g_cfg.num_files)
    {
      printf ("penis3\n");
      /*reload();*/

      // this would pause the player [[IMPORTANTE: pause with no fadeout]]
      //player->pause(true, false); 

      // but instead let's restart the playlist
      g_cur_entry=0;
      reload();
      return true;
    }
    //goto reload;
    reload();
    return true;
  }

  return false;
}

void BaseD::update_track_tag()
{
  tag = player->track_info();

  /* decide how much time the song will play */
  if (!g_cfg.ignoretagtime) {
    song_time = (int)tag.length / 1000; //atoi((const char *)tag.seconds_til_fadeout);
    if (song_time <= 0) {
      song_time = g_cfg.defaultsongtime;
    }
  }
  else {
    song_time = g_cfg.defaultsongtime;
  }

  song_time += g_cfg.extratime;

  // Outdated -- should be removed!
  now_playing[0] = 0;
  if (strcmp(tag.song, ""))
  {
    if (strlen((const char *)tag.song)) {
      sprintf(now_playing, "Now playing: %s (%s), dumped by %s\n", tag.song, tag.game, tag.dumper);
    }   
  }
  if (strlen(now_playing)==0) {
    sprintf(now_playing, "Now playing: %s\n", g_cfg.playlist[g_cur_entry]);
  }
}

void BaseD::start_track( int track, const char* path )
{
  handle_error( player->start_track( track - 1 ) );
  
  // update window title with track info
  long seconds = player->track_info().length / 1000;
  const char* game = player->track_info().game;
  if ( !*game )
  {
    // extract filename
    game = strrchr( path, '\\' ); // DOS
    if ( !game )
      game = strrchr( path, '/' ); // UNIX
    if ( !game )
    {
      if (path)
        game = path;
      else game = "";
    }
    else
      game++; // skip path separator
  }
  
  char title [512];
  sprintf( title, "%s: %d/%d %s (%ld:%02ld)",
      game, track, player->track_count(), player->track_info().song,
      seconds / 60, seconds % 60 );
  SDL_SetWindowTitle(sdlWindow, title);
}

// Needs to be properly decoupled the main_window impl and BaseD impl
void BaseD::reload(char **paths/*=NULL*/, int numpaths/*=0*/)
{
  char *path=NULL;
  bool using_playlist=false;
  
  if (!paths)
  {
    DEBUGLOG("A");
    using_playlist=true;
    if (g_cfg.playlist[g_cur_entry])
      path = g_cfg.playlist[g_cur_entry];
    else path = NULL;
  }
  else
  {
    DEBUGLOG("B");
    g_cur_entry = 0;
    g_cfg.playlist = paths;
    g_cfg.num_files = numpaths;
    path = g_cfg.playlist[g_cur_entry];
  }



  //DEBUGLOG("path = %d\n", path);
  if (path == NULL)
  {
    //using_playlist = false;
    player->has_no_song = true;
    return; 
  }

  DEBUGLOG("g_cfg.playlist = %lx\n", (uintptr_t)g_cfg.playlist);
  DEBUGLOG("g_cur_entry = %d", g_cur_entry);
  DEBUGLOG("g_cfg.playlist[g_cur_entry] = %s\n", g_cfg.playlist[g_cur_entry]);

#ifdef _WIN32
  g_real_filename = strrchr(path, '\\');
#else
  g_real_filename = strrchr(path, '/');
#endif
  if (!g_real_filename) {
    g_real_filename = path;
  }
  else {
    // skip path sep
    g_real_filename++;
  }

  // Load file
  BaseD::path = path;
  handle_error( player->load_file( path ) );
  
  IAPURAM = player->spc_emu()->ram();
  
  report::memsurface.clear();

  memset(report::used, 0, sizeof(report::used));
  memset(report::used2, 0, sizeof(report::used2));
  report::last_pc = -1;
  player->mute_voices(voice_control.muted);
  start_track( 1, path );
  
  player->ignore_silence();

  // update Window Title
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

  update_track_tag();
  
  STUB("FIXME draw_track_tag signal to mainwindow");
  // if (grand_mode == MAIN)
  //   main_window->draw_track_tag();

  char title [512];
  //if (using_playlist)
  //{
    sprintf( title, "%s: %d/%d %s (%ld:%02ld)",
        game, g_cur_entry+1, g_cfg.num_files, player->track_info().song,
        seconds / 60, seconds % 60 );
  /*}
  else
  {
    sprintf( title, "%s: %d/%d %s (%ld:%02ld)",
        game, 1, 1, player->track_info().song,
        seconds / 60, seconds % 60 );
  }*/
  STUB("FIXME setmainwindow title");
  //main_window->set_window_title(title);
}

void BaseD::restart_track()
{
  //player->fade_out();
  //SDL_PauseAudioDevice(Audio_Context::audio->devices.id, 1);
  g_cur_entry=0;
  //player->pause(0);
  reload();
}

void BaseD::prev_track()
{
  //player->fade_out();
  //SDL_PauseAudioDevice(Audio_Context::audio->devices.id, 1);
  g_cur_entry--;
  if (g_cur_entry<0) { g_cur_entry = g_cfg.num_files-1; }
  reload();
}

void BaseD::next_track25()
{
  g_cur_entry+=25;
  if (g_cur_entry>=g_cfg.num_files)
  { 
    int derp =  g_cur_entry - g_cfg.num_files;
    if (derp < g_cfg.num_files)
      g_cur_entry = derp;
    else g_cur_entry=g_cfg.num_files-1;
  }
}

void BaseD::prev_track25()
{
  g_cur_entry-=25;
  int tmp = abs(g_cur_entry);
  if ((unsigned)g_cur_entry>=g_cfg.num_files)
  { 
    if ((unsigned)(g_cfg.num_files-tmp) < g_cfg.num_files)
      g_cur_entry=g_cfg.num_files-tmp;  
    else 
      g_cur_entry = 0;
    
  }
}

void BaseD::next_track()
{
  
  //player->fade_out();
  //SDL_PauseAudioDevice(Audio_Context::audio->devices.id, 1);
  g_cur_entry++;
  if (g_cur_entry>=g_cfg.num_files) { g_cur_entry = 0; }
  reload();
}

void BaseD::restart_current_track()
{
  report::memsurface.clear();
  player->fade_out();
  player->start_track(0); // based on only having 1 track
  //player->pause(0);
  // in the program .. this would have to change otherwise
}




///////// MASK FUNCS ///////////

void BaseD::pack_mask(unsigned char packed_mask[32])
{
  int i;
  
  memset(packed_mask, 0, 32);
  for (i=0; i<256; i++)
  {
    if (report::used2[i])
    packed_mask[i/8] |= 128 >> (i%8);
  }
}

void BaseD::applyBlockMask(char *filename)
{
  FILE *fptr;
  unsigned char nul_arr[256];
  int i;

  memset(nul_arr, g_cfg.filler, 256);
  
  fptr = fopen(filename, "r+");
  if (!fptr) { perror("fopen"); }

  printf("[");
  for (i=0; i<256; i++)
  {
    fseek(fptr, 0x100+(i*256), SEEK_SET);
    
    if (!report::used2[i]) {
      printf(".");
      fwrite(nul_arr, 256, 1, fptr);
    } else {
      printf("o");
    }
    fflush(stdout);
  }
  printf("]\n");
  
  fclose(fptr);
}


void BaseD::write_mask(unsigned char packed_mask[32])
{
  FILE *msk_file;
  char *sep;
  char filename[1024];
  unsigned char tmp;
  int i;
  strncpy(filename, g_cfg.playlist[g_cur_entry], 1024);
#ifdef _
  WIN32
  sep = strrchr(filename, '\\');
#else
  sep = strrchr(filename, '/');
#endif
  // keep only the path
  if (sep) { sep++; *sep = 0; } 
  else { 
    filename[0] = 0; 
  }

  // add the filename
  strncat(filename, g_real_filename, 1024);

  // but remove the extension if any
  sep = strrchr(filename, '.');
  if (sep) { *sep = 0; }

  // and use the .msk extension
  strncat(filename, ".msk", 1024);

  msk_file = fopen(filename, "wb");
  if (!msk_file) {
    perror("fopen");
  }
  else
  {
    fwrite(packed_mask, 32, 1, msk_file);
  }

  printf("Writing mask to '%s'\n", filename);

  // the first 32 bytes are for the 256BytesBlock mask
  printf("256 Bytes-wide block mask:\n");
  for (i=0; i<32; i++) {
    printf("%02X",packed_mask[i]);
  }
  printf("\n");

  printf("Byte level mask..."); fflush(stdout);
  memset(packed_mask, 0, 32);
  for (i=0; i<65536; i+=8)
  {
    tmp = 0;
    if (report::used[i]) tmp |= 128;
    if (report::used[i+1]) tmp |= 64;
    if (report::used[i+2]) tmp |= 32;
    if (report::used[i+3]) tmp |= 16;
    if (report::used[i+4]) tmp |= 8;
    if (report::used[i+5]) tmp |= 4;
    if (report::used[i+6]) tmp |= 2;
    if (report::used[i+7]) tmp |= 1;
    fwrite(&tmp, 1, 1, msk_file);
  }
  printf("Done.\n");
  fclose(msk_file);
}