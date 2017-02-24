#ifndef MULTISPRITE__H
#define MULTISPRITE__H
#include <string>
#include <vector>
#include "drawable.h"
#include "explodingSprite.h"
#include "collisionStrategy.h"
class ExplodingSprite;

class MultiSprite : public Drawable {
public:
  MultiSprite(const std::string&);
  MultiSprite(const MultiSprite&);
  MultiSprite& operator=(const MultiSprite&);
  virtual ~MultiSprite() {
    if (explosion)
      delete explosion;
    for(unsigned int i = 0; i < strategies.size(); i++)
    {
      delete strategies[i];
    }
  } 
  
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const {
    return frames[currentFrame]; 
  }
  virtual void explode();
//  virtual void update2(const std::string &dir){}
  void setCollisionStrategy(int index) {
    strategy = strategies[index];
  }
  bool collideWith(const Drawable* d) {
    return strategy->execute(*this, *d);
  }
  virtual void lossHp(Uint32 loss) {
    if (hp >= loss)
      hp = hp - loss;
    else
      hp = 0;
  }
  Uint32 getHp() const {
    return hp;
  }
  int getFrameWidth() const {
    return frameWidth;
  }
  int getFrameHeight() const {
    return frameHeight;
  }
protected:
  ExplodingSprite *explosion;
  CollisionStrategy *strategy;
  std::vector<CollisionStrategy*> strategies;
  const std::vector<Frame *> frames;
  int worldWidth;
  int worldHeight;
  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int frameWidth;
  int frameHeight;
  bool hasDirection;// has direaction?
  Uint32 hp;
  void advanceFrame(Uint32 ticks);
};
#endif
