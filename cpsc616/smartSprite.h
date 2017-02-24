#ifndef SMARTSPRITE__H
#define SMARTSPRITE__H
#include <string>
#include <cmath>
#include "multisprite.h"

class SmartSprite : public MultiSprite {
public:
  SmartSprite(const std::string&,int w, int h);
  virtual ~SmartSprite() {

  }
  void update(Uint32 ticks);
  void goLeft() {
    if (X() > 0)
      velocityX(-abs(velocityX()));
  }
  void goRight() {
    velocityX(fabs(velocityX()));
  }
  void goUp() {
    velocityY(-fabs(velocityY()));
  }
  void goDown() {
    velocityY(fabs(velocityY()));
  }
  static void incrSafeDistance() {++safeDistance; }
  static void decrSafeDistance() { --safeDistance; }
  static float getSafeDistance() { return safeDistance; }
  void setPlayerPos(const Vector2f& p) { playerPos = p; }
 private:
  enum MODE {NORMAL, DASH};
  Vector2f playerPos;
  int playerWidth;
  int playerHeight;
  static float safeDistance;
  MODE currentMode;
  SmartSprite(const SmartSprite&);
  SmartSprite& operator=(const SmartSprite&);
};
#endif
