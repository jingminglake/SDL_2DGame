#include "player.h"
#include "sound.h"

//void Player::draw() const
//{
//}

Player::Player(const Player& p) :
  MultiSprite(p),
  playerVelocity(p.playerVelocity),
  direction(p.direction),
  current_ticks(p.current_ticks),
  bulletPool(p.bulletPool),
  observer(p.observer)
{
   
}

void Player::advanceFrame2(Uint32 ticks)
{
  current_ticks = ticks;
  timeSinceLastFrame += ticks;
  if (timeSinceLastFrame > frameInterval) {
    if (hasDirection)
      {
	if (direction)
	  currentFrame = (currentFrame + 1) % (numberOfFrames / 2);
	else 
	  currentFrame = (currentFrame + 1) % (numberOfFrames / 2) + (numberOfFrames / 2);
      }
    else
      currentFrame = (currentFrame+1) % numberOfFrames;
    timeSinceLastFrame = 0;
  }
}

void Player::update(Uint32 ticks)
{
  if(explosion) 
  {
    explosion->update(ticks);
    if(explosion->chunkCount() == 0) 
    {
      delete explosion;
      explosion = NULL;
    }
    return;
  }
  advanceFrame2(ticks);
  std::list<SmartSprite*>::iterator ptr = observer.begin();
  while ( ptr != observer.end() ) {
    (*ptr)->setPlayerPos( getPosition() );
    ++ptr;
  }
 }

void Player::moveUp()
{
  velocityY(-abs(playerVelocity[1]));
  move();
  update(current_ticks);
}

void Player::moveDown()
{
  velocityY(abs(playerVelocity[1]));
  move();
}

void Player::moveLeft()
{
  velocityX(-abs(playerVelocity[0]));
  direction = false;   
  move();
}

void Player::moveRight()
{
  velocityX(abs(playerVelocity[0]));
  direction = true; 
  move();
}
void Player::move()
{
  if(explosion)
     return;
  Vector2f incr = getVelocity() * ((current_ticks == 0) ? 80 : current_ticks) * 0.001 * 2;
  setPosition(getPosition() + incr);
  //std::cout << "incr--->" << incr[0] << ", " << incr[1] << std::endl; 
  if ( Y() <= 0) {
    Y(0);
  }
  if ( Y() >= worldHeight-frameHeight) {
    Y( worldHeight-frameHeight );
  }

  if ( X() <= 0) {
    X(0);
  }
  if ( X() >= worldWidth - frameWidth) {
    X( worldWidth - frameWidth);
  }
  velocityX(0);
  velocityY(0);
}

void Player::shoot()
{
  if(explosion)
     return;
  // update(current_ticks + 100);//swing faster
  bulletPool.shootOneBullet(getPosition(), direction);
  SDLSound::getInstance()[1];
}

