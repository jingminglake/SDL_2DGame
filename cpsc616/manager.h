#include <vector>
#include <list>
#include <SDL.h>
#include "ioManager.h"
#include "clock.h"
#include "world.h"
#include "player.h"
#include "viewport.h"
#include "hud.h"
#include "scaledSprite.h"
#include "flakesManager.h"
#include "health.h"
#include "sound.h"
class Manager {
public:
  Manager ();
  ~Manager ();
  void play();
  // void switchSprite();
  void reset();

private:
  const bool env;
  const IOManager& io;
  Clock& clock;

  SDL_Surface * const screen;
  std::vector<World*> world;
  Viewport& viewport;

  std::list<Drawable*> sprites;
  std::list<Drawable*> explosingSprites;// store dying sprites
  Drawable* winGate;
  //std::vector<ScaledSprites>
  Player *player;
  Hud& hud;
  FlakesManager *flakesMan;
  int currentSprite;
  BulletPool& bulletPool;
  bool makeVideo;
  int frameCount;
  const std::string username;
  const std::string title;
  const int frameMax;
  Health* playerHealthBar;
  bool isWin;
  bool isFail;
  bool isGameOver;// is game over ???
  bool godMode;
  SDLSound& sound;

  void draw() const;
  void update();
  void checkCollisions();
  void init();
  void finalize();

  Manager(const Manager&);
  Manager& operator=(const Manager&);
  void makeFrame();
};
