#ifndef BULLET__H
#define BULLET__H
#include <string>
#include "drawable.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "viewport.h"
#include "smartSprite.h"
class Bullet : public Drawable 
{
public:
  Bullet(const std::string&);
  Bullet(const std::string& name, const Vector2f& position, const Vector2f& velocity);
  Bullet(const std::string& name, const Vector2f& position, const Vector2f& velocity, const Frame*f);
  Bullet(const Bullet&);
  Bullet& operator=(const Bullet&);
  ~Bullet(){}
  virtual const Frame* getFrame() const {
    return frame;
  }
  void draw() const;
  void update(Uint32 ticks);
  bool getTooFar() const {
    return tooFar;
  }
  void reset() {
    distance = 0;
    tooFar = false;
  }
private:
  const Frame * frame;
  int frameWidth;
  int frameHeight;
  int worldWidth;
  int worldHeight;
  float distance;
  float maxDistance;
  bool tooFar;
};

#endif
