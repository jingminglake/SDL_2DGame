#include "bulletPool.h"

BulletPool::BulletPool() :
  flyingBullets(),
  freeBullets_R(),
  freeBullets_L(),
  frameFactory(FrameFactory::getInstance()),
  gdata(Gamedata::getInstance())
{
}

BulletPool& BulletPool::getInstance()
{
  static BulletPool instance;
  return instance;
}

BulletPool::~BulletPool()
{
  std::list<Bullet*>::const_iterator ptr = flyingBullets.begin();
  while (ptr != flyingBullets.end())
  {
    delete *ptr;
    ptr++;
  }
  flyingBullets.clear();
  ptr = freeBullets_R.begin();
  while (ptr != freeBullets_R.end())
  {
    delete *ptr;
    ptr++;
  }
  freeBullets_R.clear();
 ptr = freeBullets_L.begin();
  while (ptr != freeBullets_L.end())
  {
    delete *ptr;
    ptr++;
  }
  freeBullets_L.clear();
}

void BulletPool::draw()
{
  std::list<Bullet*>::const_iterator ptr = flyingBullets.begin();
  while (ptr != flyingBullets.end())
  {
    (*ptr)->draw();
    // std::cout << "draw " << (*ptr)->X() << " " << (*ptr)->Y() << std::endl;
    ++ptr;
  }
}

void BulletPool::update(Uint32 ticks)
{
  std::list<Bullet*>::iterator ptr = flyingBullets.begin();
  while (ptr != flyingBullets.end())
  {
    (*ptr)->update(ticks);
    if ((*ptr)->getTooFar())
    {
      (*ptr)->reset();
      if ((*ptr)->velocityX() > 0)
      {
	//std::cout << "vel " << (*ptr)->X() << " " << (*ptr)->Y() << std::endl;
	freeBullets_R.push_back(*ptr);
      }
      else
      {
	freeBullets_L.push_back(*ptr);
      }
      ptr = flyingBullets.erase(ptr);
    }
    else
      ++ptr;
  }
}

void BulletPool::shootOneBullet(Vector2f position, bool direction)
{
  Bullet *bulletR = NULL;
  Bullet *bulletL = NULL;
  std::list<Bullet*>::const_iterator ptr;
  if (direction)
  {
    if ( freeBullets_R.empty() )
    {
      bulletR = new Bullet("bulletR", position, Vector2f(abs(gdata.getXmlFloat("bulletR/speedX")),gdata.getXmlFloat("bulletR/speedY")));
      freeBullets_R.push_back(bulletR);
    }
    else
    {
      ptr = freeBullets_R.begin();
      (*ptr)->setPosition(position + Vector2f(95,55));
      // std::cout << "shoot " << (*ptr)->X() << " " << (*ptr)->Y() << std::endl;
      flyingBullets.push_back(*ptr);
      freeBullets_R.pop_front();
    }
  }
  else
  {
    if ( freeBullets_L.empty() )
    {
      bulletL = new Bullet("bulletL", position, Vector2f(-abs(gdata.getXmlFloat("bulletL/speedX")),gdata.getXmlFloat("bulletL/speedY")));
      freeBullets_L.push_back(bulletL);
    }
    else
    {
      ptr = freeBullets_L.begin();
      (*ptr)->setPosition(position + Vector2f(-35,55));
      // std::cout << "shoot " << (*ptr)->X() << " " << (*ptr)->Y() << std::endl;
      flyingBullets.push_back(*ptr);
      freeBullets_L.pop_front();
    }
  }
}

bool BulletPool::collideWith(const Drawable* d)
{
  PerPixelCollisionStrategy ppcs; 
  bool flag = false;
  std::list<Bullet*>::iterator ptr = flyingBullets.begin();
  while (ptr != flyingBullets.end()) {
    if(ppcs.execute(**ptr, *d)) {
      (*ptr)->reset();
      if ((*ptr)->velocityX() > 0)
	freeBullets_R.push_back(*ptr);
      else
	freeBullets_L.push_back(*ptr);
      ptr = flyingBullets.erase(ptr);
      flag = true;
      break;
    }
    else
      ++ptr;
  }
  return flag;
}
