#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include "clock.h"
#include "gamedata.h"
#include "ioManager.h"

Clock::Clock() :
  started(false), 
  paused(false), 
  sloMo(false), 
  framesAreCapped(Gamedata::getInstance().getXmlBool("framesAreCapped")), 
  frameCap(Gamedata::getInstance().getXmlInt("frameCap")), 
  frameCountForRateCalulate(Gamedata::getInstance().getXmlInt("frameCountForRateCalulate")),
  frames(0), 
  tickSum(0),
  sumOfAllTicks(0),
  timeAtStart(0), timeAtPause(0),
  currTicks(0), prevTicks(0), ticks(0),
  gameSeconds(0),
  gameFps(0.0)
  {
    start();
  }

Clock::Clock(const Clock& c) :
  started(c.started), 
  paused(c.paused), 
  sloMo(c.sloMo), 
  framesAreCapped(c.framesAreCapped), 
  frameCap(c.frameCap),
  frameCountForRateCalulate(c.frameCountForRateCalulate), 
  frames(c.frames),
  tickSum(c.tickSum),
  sumOfAllTicks(c.sumOfAllTicks),
  timeAtStart(c.timeAtStart), timeAtPause(c.timeAtPause),
  currTicks(c.currTicks), prevTicks(c.prevTicks), ticks(c.ticks),
  gameSeconds(c.gameSeconds),
  gameFps(c.gameFps)
{
  start();
}

void Clock::update(){ 
  static unsigned int prevTime = SDL_GetTicks();
  if (sloMo)
    gameSeconds = (SDL_GetTicks() - timeAtStart)/1000;
  else
    gameSeconds = getSeconds();
  if ( frames != 0 && (0 == (frames % frameCountForRateCalulate)) )
  {
    unsigned int currentTime = SDL_GetTicks();
    gameFps = frameCountForRateCalulate * 1000.0 / (currentTime - prevTime);
    prevTime = currentTime;
  }
}

void Clock::display() const { 
  IOManager::getInstance()
    .printMessageValueAt("seconds: ", gameSeconds, 15, 30);
  // IOManager::getInstance()
    // .printMessage
  //   ValueAt("frames in sec: ", lastFrames, 10, 50);
  IOManager::getInstance()
     .printMessageValueAt("frames rate: ",  gameFps, 15, 50);
}

void Clock::toggleSloMo() {
  if( started && !sloMo ) {
    timeAtPause = SDL_GetTicks() - timeAtStart;
    sloMo = true;
  }
  else if ( started && sloMo ) {
    timeAtStart = SDL_GetTicks() - timeAtPause;
    sloMo = false;
  }
}


unsigned int Clock::getTicks() const { 
  if (paused) return timeAtPause;
  else if ( sloMo ) return 1;
  else return SDL_GetTicks() - timeAtStart; 
}

unsigned int Clock::getElapsedTicks() { 
  if (paused) return 0;
  else if ( sloMo ) return 1;

  currTicks = getTicks();
  ticks = currTicks-prevTicks;
  unsigned int delay = capFrameRate();
  prevTicks = currTicks + delay;
  ticks += delay;
  sumOfAllTicks += ticks;
  return ticks;
}

unsigned int Clock::capFrameRate() const { 
  if ( !framesAreCapped ) return 0u;
  unsigned int delay = std::max(0.0,1000.0/frameCap+0.5 - ticks);
  SDL_Delay( delay );
  return delay;
}

Clock& Clock::operator++() { 
  if ( !paused ) {
    ++frames; 
  }
  return *this;
}

void Clock::start() { 
  started = true; 
  paused = false; 
  frames = 0;
  timeAtPause = timeAtStart = SDL_GetTicks(); 
}
void Clock::pause() {
  if( started && !paused ) {
    timeAtPause = SDL_GetTicks() - timeAtStart;
    paused = true;
  }
}
void Clock::unpause() {
  if( started && paused ) {
    timeAtStart = SDL_GetTicks() - timeAtPause;
    paused = false;
  }
}

void Clock::reset() {
    gameSeconds = 0;
    gameFps = 0;
    timeAtStart = SDL_GetTicks();
    frames = 0;
    tickSum = 0;
    sumOfAllTicks = 0;
    currTicks = 0;
    prevTicks = 0;
    ticks = 0;
}
