#include "smartSprite.h"

SmartSprite::SmartSprite(const std::string& name, int w, int h) :
  MultiSprite(name),
  playerPos(),
  playerWidth(w),
  playerHeight(h),
  currentMode(NORMAL)
{
}

float distance(float x1, float y1, float x2, float y2)
{
  float x = x1-x2;
  float y = y1-y2;
  return hypot(x, y);
}

void SmartSprite::update(Uint32 ticks)
{
  MultiSprite::update(ticks);
  float x = X() + getFrame()->getWidth()/2;
  float y = Y() + getFrame()->getHeight()/2;
  float ex = playerPos[0] + playerWidth/2;
  float ey = playerPos[1] + playerHeight/2;
  float distanceToEnemy = ::distance(x, y, ex, ey);
  //std::cout << "x " << x <<"y" << y << "ex" << ex << "ey" << ey << std::endl;
  //std::cout << "distanceToEnemy: " << distanceToEnemy << std::endl;
  if ( currentMode == NORMAL ) {
    if ( distanceToEnemy < safeDistance)
      currentMode = DASH;
  }
  else if (currentMode == DASH) {
    if (distanceToEnemy > safeDistance)
      currentMode = NORMAL;
    else {
      //if (x < ex) goLeft();
      // if (x > ex) goRight();
      if (y < ey) goDown();
      if (y > ey) goUp();
    }
  }
}
