#include "hud.h"

Hud& Hud::getInstance()
{
  static Hud hud;
  return hud;
}

Hud::Hud() : 
  clock(Clock::getInstance()),
  displayed(true),
  screen(IOManager::getInstance().getScreen()),
  surf(NULL)
{
   surf = SDL_CreateRGBSurface(0,200, 350, screen->format->BitsPerPixel, screen->format->Rmask, screen->format->Gmask, screen->format->Rmask, screen->format->Amask);
}

void Hud::display() const
{
   if (!displayed)
   {
     IOManager::getInstance()
     .printStringAfterMessage(Gamedata::getInstance().getXmlStr("screenTitle"), 20, 450);
     return;
   }
   const Uint32 RED = SDL_MapRGB(screen->format, 0xff, 0, 0);
   //draw rectangle
   Draw_AALine(screen, 10, 20, 10, 370, 2.0f, RED);
   Draw_AALine(screen, 10, 20, 210, 20, 1.0f, RED);
   Draw_AALine(screen, 210, 20, 210, 370, 2.0f, RED);
   Draw_AALine(screen, 10, 370, 210, 370, 1.0f, RED);
   //draw background
   //const Uint32 BLUE = SDL_MapRGB(screen->format, 0x00, 0x00, 0xcd);
   const Uint32 WHITE = SDL_MapRGB(screen->format, 0xff, 0xff, 0xff);
   SDL_Rect rect = {0, 0, 199, 348};
   SDL_FillRect(surf, &rect, WHITE);
   SDL_SetAlpha(surf, SDL_SRCALPHA, 160);
   //  surf = SDL_CreateRGBSurface(0,189,278,32,0,0,0,0);
   SDL_Rect dest = {11, 22, 0, 0};
   SDL_BlitSurface( surf, &rect, screen, &dest );
   //draw clock
   IOManager::getInstance()
    .printMessageValueAt("seconds: ", clock.gameSeconds, 15, 30);
   IOManager::getInstance()
     .printMessageValueAt("frames rate: ", clock.gameFps, 15, 50);
   // IOManager::getInstance()
   // .printStringAfterMessage("TRACKING " + Viewport::getInstance().getObjectToTrack()->getName(), 15, 70);
   IOManager::getInstance()
     .printStringAfterMessage("G: TOGGLES GOD MODE", 15, 70);
   //draw info
   IOManager::getInstance()
     .printStringAfterMessage("F1: TOGGLES THIS HUD", 15, 100);
   IOManager::getInstance()
     .printStringAfterMessage("F4: GENERATE FRAMES", 15, 120);
   IOManager::getInstance()
     .printStringAfterMessage("R: RESTART", 15, 140);
   IOManager::getInstance()
     .printStringAfterMessage("L: TOGGLES SLO_MO", 15, 160);
   IOManager::getInstance()
     .printStringAfterMessage("P: PAUSE ", 15, 180);
   IOManager::getInstance()
     .printStringAfterMessage("A: MOVE LEFT", 15, 210);
   IOManager::getInstance()
     .printStringAfterMessage("S: MOVE DOWN", 15, 230);
   IOManager::getInstance()
     .printStringAfterMessage("D: MOVE RIGHT", 15, 250);
   IOManager::getInstance()
     .printStringAfterMessage("W: MOVE UP ", 15, 270);
   IOManager::getInstance()
     .printStringAfterMessage("SPACE: SHOOT ", 15, 300);
   IOManager::getInstance()
     .printMessageValueAt("FLYINGBULLETS: ", BulletPool::getInstance().getflyingBulletsCount(), 15, 330);
   IOManager::getInstance()
     .printMessageValueAt("FREEBULLETS: ", BulletPool::getInstance().getFreeBulletsCount(), 15, 350);
   //print name 
   IOManager::getInstance()
     .printStringAfterMessage(Gamedata::getInstance().getXmlStr("screenTitle"), 20, 450);
}

void Hud::toggleDisplay()
{
   displayed = !displayed;
}
