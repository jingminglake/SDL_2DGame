#ifndef FLAKESMANAGER__H
#define FLAKESMANAGER__H
#include "scaledSprite.h"
#include <vector>
#include <algorithm>
#include "gamedata.h"
class ScaledSpriteCompare {
public:
  bool operator()(const ScaledSprite* lhs, const ScaledSprite* rhs) {
    return lhs->getScale() < rhs->getScale();
  }
};

class FlakesManager
{
public:
  FlakesManager();
  ~FlakesManager();
  void drawSmall();
  void drawMedium();
  void drawLarge();
  void update(Uint32 ticks);
private:
  void makeFlakes();
  std::vector<ScaledSprite * > flakes;
  unsigned smallIndex;
  unsigned mediumIndex;
  unsigned largeIndex;
};

#endif
