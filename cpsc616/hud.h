#ifndef HUD__H
#define HUD__H
#include "clock.h"
#include "aaline.h"
#include "ioManager.h"
#include "viewport.h"
#include "bulletPool.h"
#include <SDL.h>
#include <SDL_ttf.h>
class Hud
{
public:
  static Hud& getInstance();
  ~Hud()
  {
    SDL_FreeSurface(surf);
  }
  void display() const;
  void toggleDisplay();
  void unDisplay()
  {
    if (displayed)
      displayed = false;
  }
private:
  Hud();
  Hud(const Hud &);
  Hud& operator=(const Hud&);
  Clock &clock;
  bool displayed;
  SDL_Surface * const screen;
  SDL_Surface *surf;
};

#endif
