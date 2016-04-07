#include "gui/Window.h"

Window::Window(int width, int height, const char *title)
{
  rc.rect.w = width;
  rc.rect.h = height;
  this->title = title;
  init();
}

void Window::init()
{
  SDL_Window &sdlWindow = rc.sdlWindow;
  SDL_Renderer &sdlRenderer = rc.sdlRenderer;
  SDL_Texture &sdlTexture = rc.sdlTexture;
  SDL_Surface &screen = rc.screen;
  Uint32 &windowID = rc.windowID;
  SDL_Rect &rect = rc.rect;

  this->destroy();
  SDL_CreateWindowAndRenderer(rect.w, rect.h, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN /*| SDL_WINDOW_BORDERLESS*/, &sdlWindow, &sdlRenderer);
  if (sdlWindow == NULL || sdlRenderer == NULL)
  {
    fprintf(stderr, "FCK\n");
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                       "Warning!",
                       "Could not create Window!",
                       NULL);
    return;
  }

  windowID = SDL_GetWindowID(sdlWindow);

  //sdlWindow = *sdlWindow;
  //SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");  // make the scaled rendering look smoother.
  SDL_RenderSetLogicalSize(sdlRenderer, rect.w, rect.h);

  screen = SDL_CreateRGBSurface(0, rect.w, rect.h, 32,
                                      0x00FF0000,
                                      0x0000FF00,
                                      0x000000FF,
                                      0xFF000000);
  sdlTexture = SDL_CreateTexture(sdlRenderer,
                                          SDL_PIXELFORMAT_RGB888,
                                          SDL_TEXTUREACCESS_STREAMING,
                                          rect.w, rect.h);

  if (screen == NULL || sdlTexture == NULL)
  {
    fprintf(stderr, "MAn we have Window::Window problems : I couldn't allocate a screen or Texture :\n");
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                       "Warning!",
                       "Window::Window() - Could not allocate screen or Texture!",
                       NULL);
    return;
  }

  // consider raising window here if APPLE
  SDL_SetWindowTitle(sdlWindow, title.c_str());
}

void Window::set_title(const char *str)
{
  SDL_SetWindowTitle(rc.sdlWindow, str);
}

void Window::destroy()
{
  rc.destroy();
}

Window::~Window()
{
  SDL_Log("~Window");
  destroy();
}

void Window::clear_screen()
{
  rc.clear_screen();
}

void Window::update_screen()
{
  rc.update_screen();
}

void Window::show()
{
  SDL_Log("Window::show()");
  SDL_ShowWindow(rc.sdlWindow);
  SDL_RaiseWindow(rc.sdlWindow);
  oktoshow = true;
  //init();
}

void Window::raise()
{
  SDL_Log("Window::raise()");
  SDL_RaiseWindow(rc.sdlWindow);
}

void Window::hide()
{
  //this->destroy();
  //SDL_SetWindowGrab(sdlWindow, SDL_FALSE);
  SDL_HideWindow(rc.sdlWindow);
  oktoshow = false;
  //SDL_SetWindowPosition(sdlWindow, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED);
}

