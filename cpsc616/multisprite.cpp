#include "multisprite.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "sound.h"

void MultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
           if (hasDirection)
           {
              if (velocityX() >= 0)
                currentFrame = (currentFrame + 1) % (numberOfFrames / 2);
              else 
                currentFrame = (currentFrame + 1) % (numberOfFrames / 2) + (numberOfFrames / 2);
           }
           else
             currentFrame = (currentFrame+1) % numberOfFrames;
           timeSinceLastFrame = 0;
	}
}

MultiSprite::MultiSprite( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  explosion(NULL),
  strategy(NULL),
  strategies(),
  frames( FrameFactory::getInstance().getFrames(name) ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight()),
  hasDirection( Gamedata::getInstance().getXmlBool(name+"/hasDirection") ),
  hp(Gamedata::getInstance().getXmlInt(name + "/hp"))
{
  strategies.push_back( new PerPixelCollisionStrategy );
  strategies.push_back( new MidPointCollisionStrategy );
  strategies.push_back( new RectangularCollisionStrategy );
  strategy = strategies[0]; 
}

MultiSprite::MultiSprite(const MultiSprite& s) :
  Drawable(s),
  explosion(NULL), 
  strategy(s.strategy),
  strategies(),
  frames(s.frames),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  frameWidth( s.frameWidth ),
  frameHeight( s.frameHeight ),
  hasDirection(s.hasDirection),
  hp(s.hp)
  {
    strategies.push_back( new PerPixelCollisionStrategy );
    strategies.push_back( new MidPointCollisionStrategy );
    strategies.push_back( new RectangularCollisionStrategy );
    strategy = strategies[0]; 
  }

MultiSprite& MultiSprite::operator=(const MultiSprite &rhs)
{
  if (this != &rhs)
  {
    Drawable::operator=(rhs);
    explosion = rhs.explosion;
    strategies.push_back( new PerPixelCollisionStrategy);
    strategies.push_back( new MidPointCollisionStrategy);
    strategies.push_back( new RectangularCollisionStrategy);
    strategy = strategies[0];
    // static_cast< std::vector<Frame *> *>(&frames) = rhs.frames;
    const std::vector<Frame *> *f = &frames;
    *const_cast< std::vector<Frame *> *>(f) = rhs.frames;
    worldWidth = rhs.worldWidth;
    worldHeight = rhs.worldHeight;
    currentFrame = rhs.currentFrame;
    numberOfFrames = rhs.numberOfFrames;
    frameInterval = rhs.frameInterval;
    timeSinceLastFrame = rhs.timeSinceLastFrame;
    frameWidth = rhs.frameWidth;
    frameHeight = rhs.frameHeight;
    hasDirection = rhs.hasDirection;
    hp = rhs.hp;
  }
  return *this;
 }

void MultiSprite::draw() const { 
  if (explosion)
  {
    explosion->draw();
    return;
  }
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frames[currentFrame]->draw(x, y);
}

void MultiSprite::update(Uint32 ticks) { 
  if (explosion)
  {
    explosion->update(ticks);
    if (explosion->chunkCount() == 0)
    {
      delete explosion;
      explosion = NULL;
      setVisible(false);
    }
    return;
  }
  advanceFrame(ticks);
  //change position  
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( Y() < 0) {
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > worldHeight-frameHeight) {
    velocityY( -abs( velocityY() ) );
  }

  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
  }  

}

void MultiSprite::explode()
{
  if (explosion) return;
  Sprite tempSprite(getName(), getPosition(), getVelocity(), getFrame());
  explosion = new ExplodingSprite(tempSprite);
  SDLSound::getInstance()[2];
}
