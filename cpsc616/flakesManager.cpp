#include "flakesManager.h"

FlakesManager::FlakesManager() :
  flakes(),
  smallIndex(0),
  mediumIndex(0),
  largeIndex(0)
{
  makeFlakes();
}


FlakesManager::~FlakesManager()
{
  for (unsigned i = 0; i < flakes.size(); ++i)
    delete flakes[i];
  flakes.clear();
}  

void FlakesManager::drawSmall()
{
  for (unsigned i = 0; i <= smallIndex; ++i) {
    flakes[i]->draw();
  }  
}

void FlakesManager::drawMedium()
{
  for (unsigned i = smallIndex + 1; i <= mediumIndex; ++i) {
    flakes[i]->draw();
  } 
}

void FlakesManager::drawLarge()
{
  for (unsigned i = mediumIndex + 1; i <= largeIndex; ++i) {
    flakes[i]->draw();
  } 
}

void FlakesManager::update(Uint32 ticks)
{
  std::vector<ScaledSprite *>::iterator ptr
    = flakes.begin();
  while (ptr != flakes.end())
  {
    (*ptr)->update(ticks);
    ++ptr;
  }
}

void FlakesManager::makeFlakes()
{
  unsigned numberOfFlakes = Gamedata::getInstance().getXmlInt("numberOfFlakes");
  flakes.reserve( numberOfFlakes );
  for (unsigned i = 0; i < numberOfFlakes; ++i) {
    flakes.push_back( new ScaledSprite("flakes") );
  }
  std::sort(flakes.begin(), flakes.end(), ScaledSpriteCompare());
  //  for (unsigned i = 0; i < flakes.size(); ++i) {
  //  std::cout << " flakes[i]->getScale() " << flakes[i]->getScale() << std::endl;
  //}
  for (unsigned i = 0; i < flakes.size(); ++i) {
    //std::cout << " flakes[i]->getScale() " << flakes[i]->getScale() << std::endl;  
    if (flakes[i]->getScale() <= 0.8)
    {
      flakes[i]->velocityY(flakes[i]->velocityY() - 30);
      smallIndex = i;
    }
    if (flakes[i]->getScale() <= 1.2)
    {
      flakes[i]->velocityY(flakes[i]->velocityY() - 15);
      mediumIndex = i;
    }
    if (flakes[i]->getScale() <= 1.5)
    {
      // flakes[i]->velocityY(flakes[i]->velocityY() - 10);
      largeIndex = i;
    }
  }  
  //std::cout << "smallIndex->" << smallIndex 
  //          << "mediumIndex->" << mediumIndex
  //          <<  "largeIndex->" << largeIndex << std::endl;
}
