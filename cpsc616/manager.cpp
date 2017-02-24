#include <iostream>
#include <string>
#include <iomanip>
#include "multisprite.h"
#include "smartSprite.h"
#include "sprite.h"
#include "gamedata.h"
#include "manager.h"

Manager::~Manager() { 
  finalize();
}

void Manager::init()
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  SDL_WM_SetCaption(title.c_str(), NULL);
  atexit(SDL_Quit);
  sound.startMusic();
  world.push_back(new World("back", Gamedata::getInstance().getXmlInt("back/factor")));
  // world.push_back(new World("back2", Gamedata::getInstance().getXmlInt("back2/factor")));
  world.push_back(new World("back3", Gamedata::getInstance().getXmlInt("back3/factor")));
  world.push_back(new World("back4", Gamedata::getInstance().getXmlInt("back4/factor")));
  world.push_back(new World("back5", Gamedata::getInstance().getXmlInt("back5/factor")));
  world.push_back(new World("back6", Gamedata::getInstance().getXmlInt("back6/factor")));
  //sprites.push_back( new MultiSprite("spinstar") );
  //sprites.push_back( new MultiSprite("pidgeot") );
  //sprites.push_back( new MultiSprite("pokeball") );
  winGate = new Sprite("winGate");
  Vector2f winGatePosition(Gamedata::getInstance().getXmlInt("world/width") - 80, (Gamedata::getInstance().getXmlInt("world/height") - 200));
  winGate->setPosition(winGatePosition);
  player = new Player("player");
  playerHealthBar = new Health(600, 14, player->getHp(), std::string("Player's HP "));
  flakesMan = new FlakesManager();
  sprites.push_back(player);
  //sprites.push_back( new MultiSprite("pokeball1") );
  //MultiSprite *ms = NULL;
  SmartSprite *ss = NULL;
  int seed = time(0);
  srand(seed);
  for(int n = 0; n < 9; n++)
  {
    ss = new SmartSprite("swan_s", player->getFrameWidth(), player->getFrameHeight());
    Vector2f pos(rand()% Gamedata::getInstance().getXmlInt("world/width"), rand()% Gamedata::getInstance().getXmlInt("world/height"));
    ss->setPosition(pos);
    ss->velocityX((rand()%2?1:-1) * ss->velocityX());
    ss->velocityY((rand()%2?1:-1) * ss->velocityY());
    player->attach(ss);
    sprites.push_back(ss);
    Vector2f pos1(rand()% Gamedata::getInstance().getXmlInt("world/width"), rand()% Gamedata::getInstance().getXmlInt("world/height"));
    ss = new SmartSprite("swan_m", player->getFrameWidth(), player->getFrameHeight());
    ss->setPosition(pos1);
    ss->velocityX((rand()%2?1:-1) * ss->velocityX());
    ss->velocityY((rand()%2?1:-1) * ss->velocityY());
    player->attach(ss);
    sprites.push_back(ss);
    Vector2f pos2(rand()% Gamedata::getInstance().getXmlInt("world/width"), rand()% Gamedata::getInstance().getXmlInt("world/height"));
    ss = new SmartSprite("swan_l", player->getFrameWidth(), player->getFrameHeight());
    ss->setPosition(pos2);
    ss->velocityX((rand()%2?1:-1) * ss->velocityX());
    ss->velocityY((rand()%2?1:-1) * ss->velocityY());
    player->attach(ss);
    sprites.push_back(ss);
  }
  // sprites.push_back( new MultiSprite("swan_s") );
  //sprites.push_back( new MultiSprite("swan_m") );
  // sprites.push_back( new MultiSprite("swan_l") );
  // sprites.push_back( new MultiSprite("bluebird_s") );
  // sprites.push_back( new MultiSprite("bluebird_l") );
  //sprites.push_back( new Sprite("star") );
  //sprites.push_back( new Sprite("greenorb") );
  std::list<Drawable*>::const_iterator ptr = sprites.begin();
  isWin = false;
  isFail = false;
  isGameOver = false;
  godMode = false;
  viewport.setObjectToTrack(*ptr);
  //viewport.setObjectToTrack(player);
}

void Manager::finalize()
{
  // These deletions eliminate "definitely lost" and
  // "still reachable"s in Valgrind.
  std::cout << "Manager::finalize()" << std::endl;
  std::list<Drawable*>::const_iterator ptr = sprites.begin();
  sound.stopMusic();
  while (ptr != sprites.end()) {
    delete *ptr;
    ++ptr;
  }
  sprites.clear();

  ptr = explosingSprites.begin();
  while (ptr != explosingSprites.end()) {
    delete *ptr;
    ++ptr;
  }
  explosingSprites.clear();

  for (unsigned i = 0; i < world.size(); ++i) {
    delete world[i];
  }
  world.clear();
  delete flakesMan;
  delete playerHealthBar;
  delete winGate;
  //SDL_FreeSurface(screen);
}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
  //world("back", Gamedata::getInstance().getXmlInt("back/factor") ),
  world(),
  viewport( Viewport::getInstance() ),
  sprites(),
  explosingSprites(),
  winGate(),
  player(),
  hud(Hud::getInstance()),
  flakesMan(),
  currentSprite(0),
  bulletPool(BulletPool::getInstance()),
  makeVideo( false ),
  frameCount( 0 ),
  username(  Gamedata::getInstance().getXmlStr("username") ),
  title( Gamedata::getInstance().getXmlStr("screenTitle") ),
  frameMax( Gamedata::getInstance().getXmlInt("frameMax") ),
  playerHealthBar(),
  isWin(false),
  isFail(false),
  isGameOver(false),
  godMode(false),
  sound(SDLSound::getInstance())
{
  init();
}

void Manager::draw() const {
  // std::vector<World*>::const_iterator ptr = world.begin();
  /*  while (ptr != world.end())
  {
     (*ptr)->draw();
     ++ptr;
  }*/
  /*for(unsigned i = 0; i < world.size(); ++i)
  {
    if(i)
  }*/
  world[0]->draw();
  flakesMan->drawSmall();
  world[1]->draw();
  world[2]->draw();
  flakesMan->drawMedium();
  world[3]->draw();
  world[4]->draw();
  flakesMan->drawLarge();
  playerHealthBar->draw();
  winGate->draw();
  std::list<Drawable*>::const_iterator ptr0 = sprites.begin();
  while (ptr0 != sprites.end()) {
    (*ptr0)->draw();
    ++ptr0;
  }
  ptr0 = explosingSprites.begin();
  while (ptr0 != explosingSprites.end()) {
    if ((*ptr0)->isVisible()) {
      (*ptr0)->draw();
    }
    ++ptr0;
  }
  bulletPool.draw();
  //io.printMessageValueAt("Seconds: ", clock.getSeconds(), 10, 20);
  if (isWin)
  {
    IOManager::getInstance().printMessageAt("Congratulations !!! You Win The Game!!!", 280, 220);
    // set all sprites velocity to 0
    ptr0 = sprites.begin();
    // ptr0++;
    while (ptr0 != sprites.end())
    {
      (*ptr0)->velocityX(0);
      (*ptr0)->velocityY(0);
      ++ptr0;
    }
  }
  if (isFail)
  {
    IOManager::getInstance().printMessageAt("You Loss The Game!!! Press R to Retry", 280, 220);
     // set all sprites velocity to 0
    ptr0 = sprites.begin();
    while (ptr0 != sprites.end())
    {
      (*ptr0)->velocityX(0);
      (*ptr0)->velocityY(0);
      ++ptr0;
    }
  } 
  //io.printMessageAt("Press T to switch sprites", 10, 70);
  //io.printMessageAt(title, 10, 540);
  hud.display();
  unsigned int ticks = clock.getTotalTicks();
  if(ticks > 2100 && ticks < 2500)
    hud.unDisplay();
  //std::cout << "ticks-->" << clock.getTicks() << std::endl;
  //std::cout << "allticks-->" << clock.getTotalTicks() << std::endl;
  //viewport.draw();
  SDL_Flip(screen);
}

void Manager::makeFrame() {
  std::stringstream strm;
  strm << "frames/" << username<< '.'
       << std::setfill('0') << std::setw(4)
       << frameCount++ << ".bmp";
  std::string filename( strm.str() );
  std::cout << "Making frame: " << filename << std::endl;
  SDL_SaveBMP(screen, filename.c_str());
}

/*void Manager::switchSprite() {
  currentSprite = (currentSprite+1) % sprites.size();
  viewport.setObjectToTrack(sprites[currentSprite]);
  }*/

void Manager::update() {
  ++clock;
  Uint32 ticks = clock.getElapsedTicks();
  clock.update();
  static unsigned int lastSeconds = clock.getSeconds();
  if ( clock.getSeconds() - lastSeconds == 5 ) {
    lastSeconds = clock.getSeconds();
    //switchSprite();
  }
  flakesMan->update(ticks);
  bulletPool.update(ticks);
  std::list<Drawable*>::iterator ptr0 = sprites.begin();
  while (ptr0 != sprites.end()) {
    (*ptr0)->update(ticks);
    ++ptr0;
  }
  ptr0 = explosingSprites.begin();
  while (ptr0 != explosingSprites.end()) {
    if ((*ptr0)->isVisible())
      (*ptr0)->update(ticks);
    ++ptr0;
  }
  if ( makeVideo && frameCount < frameMax ) {
    makeFrame();
  }
  std::vector<World*>::const_iterator ptr = world.begin();
  while (ptr != world.end())
  {
    (*ptr)->update();
    ++ptr;
  }

  viewport.update(); // always update viewport last
}

void Manager::checkCollisions()
{
  /*collision between player and enimies*/
  std::list<Drawable *>::iterator ptr = sprites.begin();
  ptr++;
  while (ptr != sprites.end())
  {
    if (player->collideWith(*ptr))
    {
      if (!godMode)
      {
        player->explode();
        player->lossHp(40);// loss 40 hp when collideWith one enimies
        playerHealthBar->update2(40); // update the health bar
        if (player->getHp() == 0 && !isGameOver) {
          isFail = true;
          //sound[1];
          isGameOver = true;
        }
      }
      (*ptr)->explode();
      explosingSprites.push_back(*ptr);
      ptr = sprites.erase(ptr);
    }
    else
      ++ptr;
  }
  /*collsion between bullets and enimies*/
  ptr = sprites.begin();
  ++ptr;
  while (ptr != sprites.end())
  {
    if (bulletPool.collideWith(*ptr))
    {
      (*ptr)->explode();
      explosingSprites.push_back(*ptr);
      ptr = sprites.erase(ptr);
    }
    else
      ++ptr;
  }
   /*collision between player and winGate : win!!!*/
  if (player->collideWith(winGate) && !isGameOver)
  {
    isWin = true;
    sound[0];
    isGameOver = true;
  }
}

void Manager::reset()
{
  clock.reset();
  finalize();
  init();
}

void Manager::play() {
  SDL_Event event;
  bool done = false;

  while ( not done ) {
     Uint8 *keystate = SDL_GetKeyState(NULL);
     if ( SDL_PollEvent(&event) ) { 
      if (event.type ==  SDL_QUIT) { 
          done = true; 
          //break; 
      }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
          done = true;
          //break;
        }
        if ( keystate[SDLK_l] ) {
          clock.toggleSloMo();
        }
        if ( keystate[SDLK_p] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if (keystate[SDLK_F1]) {
          hud.toggleDisplay();
        }
        if (keystate[SDLK_F4] && !makeVideo) {
          std::cout << "Making video frames" << std::endl;
          makeVideo = true;
        }
        if (keystate[SDLK_SPACE]) {
          player->shoot();
        }
        if (keystate[SDLK_g]) {
	  godMode = !godMode;
        }
	if (keystate[SDLK_r]) {
	  reset();
        }
      }
    }
    if (keystate[SDLK_a]) {
	  player->moveLeft();
    }
    if (keystate[SDLK_d])
    {
      player->moveRight();
    }
    if (keystate[SDLK_w]) {
      player->moveUp();
    }
    if (keystate[SDLK_s]) {
      player->moveDown();
    }
    checkCollisions();
    draw();
    update();
  }
}
