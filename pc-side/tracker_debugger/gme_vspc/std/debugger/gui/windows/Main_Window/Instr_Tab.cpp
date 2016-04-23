#include "Instr_Tab.h"
#include "sdlfont.h"
#include "utility.h"
#include "report.h"
#include "gme/Spc_Dsp_Register_Map_Interface.h"
#include "Notes.h"
#include "platform.h"
#include "stub.h"
#include "Midi.h"
void Instr_Tab::activate()
{
  // register callback
  STUB("Instr_Tab::activate");
}

void Instr_Tab::deactivate()
{
  // deactivate callback
  STUB("Instr_Tab::deactivate");
}

int Instr_Tab::midi_callback(double deltatime, jdkmidi::MIDIMessage *m, void *userData)
{
  // Send the note to the main app
  if (m->IsNoteOn())
  {
      SDL_Event event2;

      event2.type = SDL_USEREVENT;
      event2.user.code = UserEvents::play_pitch;
      event2.user.data1 = (void*)m->GetNote();
      event2.user.data2 = 0;
      SDL_PushEvent(&event2);
      last_note_on = m->GetNote();
  }
  else if (m->IsNoteOff())
  {
    if (m->GetNote() == last_note_on)
    {
      SDL_Event event2;

      event2.type = SDL_USEREVENT;
      event2.user.code = UserEvents::keyoff;
      event2.user.data1 = (void*)m->GetNote();
      event2.user.data2 = 0;
      SDL_PushEvent(&event2);
    }
  }
  else if (m->IsProgramChange())
  {
    set_voice(m->GetPGValue());
  }
}


Instr_Tab::Instr_Tab(int x, int y) :
start_x(x), start_y(y),
octave("octave"),
voice("voice")
{

}

void Instr_Tab::pause_spc()
{
  start_stop.is_started = true;
  BaseD::Hack_Spc::pause_spc();
}
void Instr_Tab::restore_spc(bool resume/*=true*/)
{
  start_stop.is_started = false;
  BaseD::Hack_Spc::restore_spc(resume);
}

void Instr_Tab::run()
{
  report::last_pc = (int)player->spc_emu()->pc(); 

  /* Check if it is time to change tune.
   */   
  if (BaseD::check_time())
  {
    start_stop.is_started = false;
    BaseD::Hack_Spc::is_started = false;
  }

  //int current_voice = voice.n;
  //voice.update_adsr_vals();
  adsr1 = player->spc_read_dsp(0x10*voice.n + dsp_reg::adsr1);
  adsr2 = player->spc_read_dsp(0x10*voice.n + dsp_reg::adsr2);

  adsr_context_menus.update(adsr1, adsr2);

  //Uint8 envx = player->spc_read_dsp(0x10*voice.n + dsp_reg::envx);
  /*if (envx)
  {
    if (!started)
    {
      
      started = true;
      mytime = SDL_GetTicks();
    }
  }
  else if (started)
  {
    fprintf(stderr, "envx: %d\n", SDL_GetTicks() - mytime);
    started = false;
  }*/
  
  

  if (is_first_run)
  {
    one_time_draw();

    is_first_run = false;
  }
}

void Instr_Tab::one_time_draw()
{
  int x = start_x, o_x=x;
  int y = start_y;
  int o_y = y;

    voice.label.rect.x = x;
    voice.label.rect.y = y;

    x+=1*TILE_WIDTH;//center
    y+=TILE_HEIGHT;
    y+=TILE_HEIGHT;
    voice.left_arrow.rect.x = x;
    voice.left_arrow.rect.y = y;
    x += TILE_WIDTH;
    voice.n_x = x;
    voice.n_y = y;
    //y+=TILE_HEIGHT;
    x += TILE_WIDTH;
    voice.right_arrow.rect.x = x;
    voice.right_arrow.rect.y = y;
    
    y=o_y;
    x=o_x;
    x+=voice.label.rect.w + 2*TILE_WIDTH;

    octave.label.rect.x = x;
    octave.label.rect.y = y;
    x+=3*TILE_WIDTH; // center
    y+=TILE_HEIGHT;
    octave.up_arrow.rect.x = x;
    octave.up_arrow.rect.y = y;
    y+=TILE_HEIGHT;
    octave.n_x = x;
    octave.n_y = y;
    y+=TILE_HEIGHT;
    octave.down_arrow.rect.x = x;
    octave.down_arrow.rect.y = y;

    y +=(CHAR_HEIGHT*3);
    sprintf(tmpbuf, "ADSR");
    sdlfont_drawString(screen, voice.n_x, y, tmpbuf, Colors::gray);
    adsr.x = voice.n_x;
    adsr.y = y;
    y+= 2*CHAR_HEIGHT;
    
    int save_y = y;
    sprintf(tmpbuf, "Attack");
    sdlfont_drawString(screen, voice.n_x, y, tmpbuf, Colors::gray); 
    attack.x = voice.n_x;
    attack.y = y;
    y+= CHAR_HEIGHT;
    adsr_context_menus.attack_context.menu.preload(voice.n_x, y);
    
    //
    decay.x = attack.x + (CHAR_WIDTH*(4+strlen("Attack")));
    decay.y = save_y;
    sprintf(tmpbuf, "Decay");
    sdlfont_drawString(screen, decay.x, decay.y, tmpbuf, Colors::gray);
    y = decay.y + CHAR_HEIGHT;
    adsr_context_menus.decay_context.menu.preload(decay.x, y);

    sustain_level.x = decay.x + (CHAR_WIDTH*(4+strlen("Decay")));
    sustain_level.y = save_y;
    sprintf(tmpbuf, "Sustain Level");
    sdlfont_drawString(screen, sustain_level.x, sustain_level.y, tmpbuf, Colors::gray);
    adsr_context_menus.sustain_level_context.menu.preload(sustain_level.x, y);

    sustain_release.x = sustain_level.x + (CHAR_WIDTH*(2+strlen("Sustain Level")));
    sustain_release.y = save_y;
    sprintf(tmpbuf, "Sustain Release");
    sdlfont_drawString(screen, sustain_release.x, sustain_release.y, tmpbuf, Colors::gray);
    adsr_context_menus.sustain_release_context.menu.preload(sustain_release.x, y);
}

void Instr_Tab::draw()
{
  /*if (!start_stop.is_started)
  {
    start_stop.startc.draw(Colors::red);
  }
  else start_stop.stopc.draw(Colors::red);*/
  voice.label.draw(Colors::gray);
  voice.left_arrow.draw(Colors::white, true, false, true);
    sprintf(tmpbuf, "%d", voice.n);
    sdlfont_drawString(screen, voice.n_x, voice.n_y, tmpbuf, Colors::voice[voice.n]);
  voice.right_arrow.draw(Colors::white); // Vflip

  octave.label.draw(Colors::gray);
  octave.up_arrow.draw(Colors::white);
    sprintf(tmpbuf, "%d", octave.n);
    sdlfont_drawString(screen, octave.n_x, octave.n_y, tmpbuf, Colors::magenta);
  octave.down_arrow.draw(Colors::white, true, true); // flipV


  //SDL_FillRect(screen, &attack_context.menu.created_at, Colors::black);
  
  adsr_context_menus.draw(screen);
  
  sdl_draw();
}

int Instr_Tab::receive_event(SDL_Event &ev)
{
  int r;

  if ((r=adsr_context_menus.receive_event(ev)))
  {
    switch (r)
    {
      case ADSR::Context_Menus::ATTACK_CHANGED:
      {
        Uint8 i = adsr_context_menus.attack_context.menu.currently_selected_item_index;
        Uint8 vreg = voice.n * 0x10 + dsp_reg::adsr1;
        Uint8 adsr1 = player->spc_read_dsp(vreg);
        adsr1 = adsr1 & (~ADSR::ATTACK_MASK);
        adsr1 |= ADSR::reverse_attack_index(i);
        player->spc_write_dsp(vreg, adsr1);
      }
      break;
      case ADSR::Context_Menus::DECAY_CHANGED:
      {
        Uint8 i = adsr_context_menus.decay_context.menu.currently_selected_item_index;
        Uint8 vreg = voice.n * 0x10 + dsp_reg::adsr1;
        Uint8 adsr1 = player->spc_read_dsp(vreg);
        adsr1 = adsr1 & (~ADSR::DECAY_MASK);
        adsr1 |= ADSR::reverse_decay_index(i);
        player->spc_write_dsp(vreg, adsr1);
      }
      break;
      case ADSR::Context_Menus::SUSTAIN_LEVEL_CHANGED:
      {
        Uint8 i = 7-adsr_context_menus.sustain_level_context.menu.currently_selected_item_index;
        Uint8 vreg = voice.n * 0x10 + dsp_reg::adsr2;
        Uint8 adsr2 = player->spc_read_dsp(vreg);
        adsr2 = adsr2 & (~ADSR::SUSTAIN_LEVEL_MASK);
        adsr2 |= ADSR::reverse_sustain_level_index(i);
        player->spc_write_dsp(vreg, adsr2);
      }
      break;
      case ADSR::Context_Menus::SUSTAIN_RELEASE_CHANGED:
      {
        Uint8 i = adsr_context_menus.sustain_release_context.menu.currently_selected_item_index;
        Uint8 vreg = voice.n * 0x10 + dsp_reg::adsr2;
        Uint8 adsr2 = player->spc_read_dsp(vreg);
        adsr2 = adsr2 & (~ADSR::SUSTAIN_RELEASE_MASK);
        adsr2 |= ADSR::reverse_sustain_release_index(i);
        player->spc_write_dsp(vreg, adsr2);
      }
      break;
      default:break;
    }
    return;
  }




  dblclick::check_event(&ev);



  switch (ev.type)
  {
    
    case SDL_QUIT:
      /*if (!g_cfg.nosound) {
        SDL_PauseAudioDevice(Audio_Context::audio->devices.id, 1);
      }*/
      printf ("penis4\n");
      BaseD::quitting = true;
      break;
    case SDL_MOUSEMOTION:
      {
        mouse::x = ev.motion.x; mouse::y = ev.motion.y;
      }
      break;
    case SDL_KEYUP:
      //scancode = 0;
      // should really have a list of SDLK for keyboard playing
      if (ev.key.keysym.sym != SDLK_LEFT && ev.key.keysym.sym != SDLK_RIGHT)
        if (scancode == ev.key.keysym.sym) 
          keyoff_current_voice();
      //SDL_Delay(1000);
      
      //fprintf(stderr, "DERP");
    break;
    case SDL_KEYDOWN:
    {
      //if (scancode == ev.key.keysym.sym)
        //break;
      if (ev.key.repeat != 0)
      break;
      scancode = ev.key.keysym.sym;
      switch (scancode)
      {
        case SDLK_SPACE: // toggle pause
          if (BaseD::Hack_Spc::is_started)
          {
            restore_spc();
            start_stop.is_started = false;
          }
          else player->toggle_pause();
        break;
        default:break;
      }
      if (ev.key.keysym.mod & (CMD_CTRL_KEY))
      {
        //is_shift_pressed=true;
        switch (scancode)
        {
          case SDLK_LEFT:
            BaseD::Hack_Spc::is_started = false;
            prev_track();

          break;
          case SDLK_RIGHT:
            BaseD::Hack_Spc::is_started = false;
            next_track();
            break;
          case SDLK_UP:
            inc_voice();
          break;
          case SDLK_DOWN:
            dec_voice();
          break;
          default:break;
        } 
        break;
      }
      
      switch (scancode)
      {
        case SDLK_ESCAPE:
          quitting=true;
        break;
        case SDLK_TAB:
          if (ev.key.keysym.mod & KMOD_SHIFT)
          {
            BaseD::Hack_Spc::is_started=false;
            prev_track25();
          }
          else 
          {
            BaseD::Hack_Spc::is_started=false;
            next_track25();
          }
          //goto reload;
          this->reload();
        break;

        case SDLK_LEFT:
          dec_voice();
          break;
        case SDLK_RIGHT:
          inc_voice();
          break;

        case SDLK_z:
          //
          play_pitch(0);
          mytime= SDL_GetTicks();
        break;
        case SDLK_s:
          play_pitch(1);
        break;
        case SDLK_x:
          play_pitch(2);
        break;
        case SDLK_d:
          play_pitch(3);
        break;
        case SDLK_c:
          play_pitch(4);
        break;
        case SDLK_v:
          play_pitch(5);
        break;
        case SDLK_g:
          play_pitch(6);
        break;
        case SDLK_b:
          play_pitch(7);
        break;
        case SDLK_h:
          play_pitch(8);
        break;
        case SDLK_n:
          play_pitch(9);
        break;
        case SDLK_j:
          play_pitch(10);
        break;
        case SDLK_m:
          play_pitch(11);
        break;
        case SDLK_COMMA:
        case SDLK_q:
          play_pitch(12);
        break;
        case SDLK_l:
        case SDLK_2:
          play_pitch(13);
        break;
        case SDLK_PERIOD:
        case SDLK_w:
          play_pitch(14);
        break;
        case SDLK_SEMICOLON:
        case SDLK_3:
          play_pitch(15);
        break;
        case SDLK_SLASH:
        case SDLK_e:
          play_pitch(16);
        break;
        case SDLK_r:
          play_pitch(17);
        break;
        case SDLK_5:
          play_pitch(18);
        break;
        case SDLK_t:
          play_pitch(19);
        break;
        case SDLK_6:
          play_pitch(20);
        break;
        case SDLK_y:
          play_pitch(21);
        break;
        case SDLK_7:
          play_pitch(22);
        break;
        case SDLK_u:
          play_pitch(23);
        break;
        case SDLK_i:
          play_pitch(24);
        break;
        case SDLK_9:
          play_pitch(25);
        break;
        case SDLK_o:
          play_pitch(26);
        break;
        case SDLK_0:
          play_pitch(27);
        break;
        case SDLK_p:
          play_pitch(28);
        break;
        case SDLK_LEFTBRACKET:
          play_pitch(29);
        break;
        case SDLK_EQUALS:
          play_pitch(30);
        break;
        case SDLK_RIGHTBRACKET:
          play_pitch(31);
        break;

        //
        case SDLK_UP:
          inc_octave();
        break;
        case SDLK_DOWN:
          dec_octave();
        break;


        default:
          break;
      }
      

    }
      break;

    case SDL_USEREVENT:
    {
      if (ev.user.code == UserEvents::mouse_react)
      {
        //SDL_Event *te = (SDL_Event *)ev.user.data1; // the mouse coordinates at time of double click
      }
      else if (ev.user.code == UserEvents::play_pitch)
      {
        uintptr_t tmp = (uintptr_t)ev.user.data1;
        unsigned char pitch = (unsigned char)tmp;
        play_pitch(pitch - Notes::midi_offset, true);
      }
      else if (ev.user.code == UserEvents::keyoff)
      {
        keyoff_current_voice();
      }
    } break;
    case SDL_MOUSEWHEEL:
    {
      
    } break;
    case SDL_MOUSEBUTTONDOWN:           
    {
      if (adsr_context_menus.check_left_click_activate(ev.button.x, ev.button.y))
      {
        return;
      }
      
      /*if (Utility::coord_is_in_rect(ev.button.x, ev.button.y, &start_stop.startc.rect))
      {
        if (!start_stop.is_started)
        {
          pause_spc();
          start_stop.is_started = true;
        }
        else
        {
          restore_spc();
          start_stop.is_started = false;
        }
      }*/


      if (Utility::coord_is_in_rect(ev.button.x, ev.button.y, &voice.right_arrow.rect))
      {
        inc_voice();
      }
      else if (Utility::coord_is_in_rect(ev.button.x, ev.button.y, &voice.left_arrow.rect))
      {
        dec_voice();
      }

      if (Utility::coord_is_in_rect(ev.button.x, ev.button.y, &octave.up_arrow.rect))
      {
        inc_octave();
      }
      else if (Utility::coord_is_in_rect(ev.button.x, ev.button.y, &octave.down_arrow.rect))
      {
        dec_octave();
      }
    }
    break;
    
    default:
    break;
  }
}

void Instr_Tab::set_voice(unsigned char v)
{
  voice.n = v % 8;
}

void Instr_Tab::inc_voice()
{
  if (voice.n == 7)
          voice.n = 0;
        else voice.n++;
}
void Instr_Tab::dec_voice()
{
  if (voice.n == 0)
          voice.n = 7;
        else voice.n--;
}

void Instr_Tab::inc_octave()
{
  if (octave.n == 6)
          octave.n = 0;
        else octave.n++;
}

void Instr_Tab::dec_octave()
{
  if (octave.n == 0)
          octave.n = 6;
        else octave.n--;
}

void Instr_Tab::play_pitch(int p, bool abs/*=false*/)
{
  if (!BaseD::Hack_Spc::is_started)
  {
    pause_spc();
  }
  player->spc_write_dsp(dsp_reg::koff, 0);
  uint8_t hi,lo;
  uint16_t index = (abs ? 0:12*octave.n) + 0x18 + 1 + p;
  if (index > Notes::pitch_table_size-1)
    return;
  hi = Notes::pitch_table[index] >> 8;
  lo = Notes::pitch_table[index] & 0xff;
  //fprintf(stderr, "p = 0x%02X%02X\n", hi, lo);
  player->spc_write_dsp(dsp_reg::plo + (voice.n*0x10), lo);
  player->spc_write_dsp(dsp_reg::phi + (voice.n*0x10), hi);
  player->spc_write_dsp(dsp_reg::kon, 1 << voice.n);
}



void Instr_Tab::keyoff_current_voice()
{
  player->spc_write_dsp(dsp_reg::koff, 1 << voice.n);
}