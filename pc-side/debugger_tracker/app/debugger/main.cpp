#include "app.h"

int main(int argc, char **argv)
{
  if (init_sdl())
    return -1;

  App app(argc, argv, 32000);
  app.run();
}












