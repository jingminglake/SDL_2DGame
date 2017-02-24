#ifndef BULLETPOOL__H
#define BULLETPOOL__H

#include "bullet.h"
#include <list>
#include "gamedata.h"
#include "collisionStrategy.h"
class BulletPool
{
public:
  static BulletPool& getInstance();
  ~BulletPool();
  void draw();//draw all flying bullets
  void update(Uint32 ticks);//update the position of flying bullets
  int getflyingBulletsCount() {
    return flyingBullets.size();
  }
  int getFreeBulletsCount() {
    return freeBullets_R.size() + freeBullets_L.size();
  }
  void shootOneBullet(Vector2f position, bool direction);
  bool collideWith(const Drawable* d);
private:
  BulletPool();
  BulletPool(const BulletPool&);
  BulletPool& operator=(const BulletPool&);
  std::list<Bullet*> flyingBullets;//flying bullets lists
  std::list<Bullet*> freeBullets_R;// bullets free in pool to right
  std::list<Bullet*> freeBullets_L;// bullets free in pool to left
  FrameFactory& frameFactory;
  Gamedata& gdata;
};

#endif
