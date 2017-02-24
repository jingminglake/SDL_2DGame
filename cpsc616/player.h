#ifndef PLAYER__H
#define PLAYER__H
#include "multisprite.h"
#include "smartSprite.h"
#include "bulletPool.h"
#include <list>
class Player : public MultiSprite
{
public:
  Player(const std::string& name):
  MultiSprite(name),
  playerVelocity(),
  direction(true), //postive,left to right
  current_ticks(0),
  bulletPool(BulletPool::getInstance()),
  observer()
  {
    playerVelocity[0] = velocityX();
    playerVelocity[1] = velocityY();
    velocityX(0);
    velocityY(0);
  }
  Player(const Player&);
  //void draw() const;
  void update(Uint32 ticks);
  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();
  void shoot();
  //const Frame* getFrame() const { }
  ~Player(){}
  void advanceFrame2(Uint32 ticks);
  void attach(SmartSprite* o) {
    observer.push_back(o);
  }
  void detach(SmartSprite* o) {
    std::list<SmartSprite*>::iterator ptr = observer.begin();
    while ( ptr != observer.end() ) {
      if ( *ptr != o ) {
        ptr = observer.erase(ptr);
        return;
      }
      ++ptr;
    }
  }
 private:
  void move();
  Vector2f playerVelocity;
  bool direction;
  Uint32 current_ticks;
  BulletPool& bulletPool;
  std::list<SmartSprite*> observer;
};


#endif
