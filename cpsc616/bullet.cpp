#include "bullet.h"

Bullet::Bullet(const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name + "/startLoc/x"), Gamedata::getInstance().getXmlInt(name + "/startLoc/y")),
	   Vector2f(Gamedata::getInstance().getXmlInt(name + "speedX"),Gamedata::getInstance().getXmlInt(name + "/speedY"))),
  frame(FrameFactory::getInstance().getFrame(name)),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  distance(0),
  maxDistance(Gamedata::getInstance().getXmlFloat(name + "/maxDistance")),
  tooFar(false)
{}

Bullet::Bullet(const std::string& name, const Vector2f& position, const Vector2f& velocity) :
  Drawable(name, position, velocity),
  frame(FrameFactory::getInstance().getFrame(name)),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  distance(0),
  maxDistance(Gamedata::getInstance().getXmlFloat(name + "/maxDistance")),
  tooFar(false)
{
}

Bullet::Bullet(const std::string& name, const Vector2f& position, const Vector2f& velocity, const Frame* f) :
  Drawable(name, position, velocity),
  frame(f),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  distance(0),
  maxDistance(Gamedata::getInstance().getXmlFloat(name + "/maxDistance")),
  tooFar(false)
{
}

Bullet::Bullet(const Bullet& b) :
  Drawable(b), 
  frame(b.frame),
  frameWidth(b.getFrame()->getWidth()),
  frameHeight(b.getFrame()->getHeight()),
  worldWidth(b.worldWidth),
  worldHeight(b.worldHeight),
  distance(b.distance),
  maxDistance(b.maxDistance),
  tooFar(b.tooFar)
{
}

Bullet& Bullet::operator=(const Bullet& rhs) {
  Drawable::operator=( rhs ),
  frame = rhs.frame;
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  distance = rhs.distance;
  maxDistance = rhs.maxDistance;
  return *this;
}


void Bullet::draw() const 
{ 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->draw(x, y); 
}

void Bullet::update(Uint32 ticks)
{
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);
  distance += abs(incr[0]);
  // std::cout << "incr-->" << incr << std::endl;
  if (distance > maxDistance) 
  {
    tooFar = true;
  }
}
