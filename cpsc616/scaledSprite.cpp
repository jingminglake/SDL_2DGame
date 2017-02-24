#include <iostream>
#include <cmath>
#include "SDL/SDL_rotozoom.h"
#include "scaledSprite.h"
#include "gamedata.h"
#include "clock.h"
ScaledSprite::ScaledSprite(const std::string& name) :
  Drawable(name,
           Vector2f(//Gamedata::getInstance().getXmlInt(name+"/loc/x"), 
                    //Gamedata::getInstance().getXmlInt(name+"/loc/y")), 
		    getRandom(0,Gamedata::getInstance().getXmlInt("world/width")),
		     getRandom(0,Gamedata::getInstance().getXmlInt("world/height"))),
           Vector2f(//(rand()%2?1:-1)*getRandom(
                    //Gamedata::getInstance().getXmlInt(name+"/cushion"),
                    //Gamedata::getInstance().getXmlInt(name+"/speed/x")),
                    //(rand()%2?1:-1)*getRandom(
                    //Gamedata::getInstance().getXmlInt(name+"/cushion"),
                    //Gamedata::getInstance().getXmlInt(name+"/speed/y"))
                    0,
                    getRandom(0, Gamedata::getInstance().getXmlInt(name+"/cushion"))
                    + Gamedata::getInstance().getXmlInt(name+"/speed/y"))                  
  ), 
  scale(getRandFloat(Gamedata::getInstance().getXmlFloat(name+"/scale/min"),
                     Gamedata::getInstance().getXmlFloat(name+"/scale/max"))
  ),
  frame(  FrameFactory::getInstance().getFrame(name)),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{
}

ScaledSprite::ScaledSprite(const ScaledSprite& s) :
  Drawable(s.getName(), s.getPosition(), s.getVelocity()), 
  scale(s.scale),
  frame(s.frame),
  frameWidth(s.frameWidth),
  frameHeight(s.frameHeight),
  worldWidth(s.worldWidth),
  worldHeight(s.worldHeight)
{ }

ScaledSprite& ScaledSprite::operator=(const ScaledSprite& rhs) {
  setName( rhs.getName() );
  setPosition(rhs.getPosition());
  setVelocity(rhs.getVelocity());
  frame = rhs.frame;
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  return *this;
}

ScaledSprite::~ScaledSprite() {
  //delete frame;
}

void ScaledSprite::draw() const { 
  //  if ( Clock::getInstance().getTotalTicks() < 2000 )
  //  return;
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->draw(x, y, 0, scale, 1); 
}

unsigned ScaledSprite::getPixel(Uint32 i, Uint32 j) const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  x = i - x;
  y = j - y;
  Uint32 *pixels = static_cast<Uint32 *>(frame->getSurface()->pixels);
  return pixels[ ( y * frame->getWidth() ) + x ];
}


void ScaledSprite::update(Uint32 ticks) { 
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( Y() < 0) {
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > worldHeight-frameHeight) {
    //velocityY( -abs( velocityY() ) );
    Y(0);
  }

  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
  }  
}
