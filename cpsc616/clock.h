#ifndef CLOCK__H
#define CLOCK__H
#include <SDL.h>
#include <string>

class Manager;
class Hud;

class Clock {
public:
  static Clock& getInstance() {
    if ( SDL_WasInit(SDL_INIT_VIDEO) == 0)  {
      throw std::string("Must init SDL before Clock");
    }
    static Clock instance; 
    return instance;
  }
  unsigned int getTicks() const;
  unsigned int getTotalTicks() const { return sumOfAllTicks; }
private:
  friend class Manager;
  friend class Hud;
  
  bool started;
  bool paused;
  bool sloMo;
  const bool framesAreCapped;
  const int frameCap;
  const int frameCountForRateCalulate;

  unsigned int frames;

  unsigned int tickSum;
  unsigned int sumOfAllTicks;
  unsigned int timeAtStart;
  unsigned int timeAtPause;
  unsigned int currTicks;
  unsigned int prevTicks;
  unsigned int ticks;
  unsigned int gameSeconds;
  double gameFps;
  unsigned int getElapsedTicks();
  Clock& operator++();
  void toggleSloMo();

  bool isStarted() const { return started; }
  bool isPaused() const  { return paused;  }
  unsigned int getFrames() const  { return frames;  }
  unsigned int getSeconds() const { return getTicks()/1000;  }
  unsigned int capFrameRate() const;
  unsigned int getGameSeconds() const { return gameSeconds;}

  void start();
  void pause();
  void unpause();
  void update();
  void display() const;
  void reset();

  Clock();
  Clock(const Clock&);
  Clock&operator=(const Clock&);
};
#endif
