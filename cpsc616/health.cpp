#include "health.h"

Health::Health() :
  screen(IOManager::getInstance().getScreen()),
  start(Vector2f(20, 100)), 
  totalLength(200), 
  currentLength(200), 
  thick(14), 
  increments(20),
  interval(1000),
  deltaTime(0),
  RED( SDL_MapRGB(screen->format, 0xff, 0x00, 0x00) ),
  GRAY( SDL_MapRGB(screen->format, 0xce, 0xb4, 0xb4) ),
  BLACK( SDL_MapRGB(screen->format, 0x00, 0x00, 0x00) ),
  color(RED),
  title("HP")
{
}

Health::Health(int sx, int sy, int tl, int cl,
               float t, int inc, Uint32 c, float sp, std::string _title):
  screen(IOManager::getInstance().getScreen()),
  start(Vector2f(sx, sy)),
  totalLength(tl),
  currentLength(cl),
  thick(t),
  increments(inc),
  interval(sp),
  deltaTime(SDL_GetTicks()),
  RED( SDL_MapRGB(screen->format, 0xff, 0x00, 0x00) ),
  GRAY( SDL_MapRGB(screen->format, 0xff, 0xff, 0xff) ),
  BLACK( SDL_MapRGB(screen->format, 0x00, 0x00, 0x00) ),
  color(c),
  title(_title)
{
}

Health::Health(int sx, int sy, int tl, std::string _title) :
  screen(IOManager::getInstance().getScreen()),
  start(Vector2f(sx, sy)),
  totalLength(tl),
  currentLength(tl),
  thick(14),
  increments(20),
  interval(1000),
  deltaTime(0),
  RED( SDL_MapRGB(screen->format, 0xff, 0x00, 0x00) ),
  GRAY( SDL_MapRGB(screen->format, 0xce, 0xb4, 0xb4) ),
  BLACK( SDL_MapRGB(screen->format, 0x00, 0x00, 0x00) ),
  color(RED),
  title(_title)
{}

void Health::drawBox() const {
  Draw_AALine(screen, start[0], start[1], 
                      start[0]+totalLength, start[1], 
                      thick, GRAY);
  // Two Horizontal lines
  Draw_AALine(screen, start[0], start[1]-8, 
                      start[0]+totalLength, start[1]-8, 
                      1.0, BLACK);
  Draw_AALine(screen, start[0], start[1]+8, 
                      start[0]+totalLength, start[1]+8, 
                      1.0, BLACK);
  // Two Vertical lines
  Draw_AALine(screen, start[0]-1, start[1]-8, 
                      start[0]-1, start[1]+8, 
                      2.0, BLACK);
  Draw_AALine(screen, start[0]+totalLength+1, start[1]-8, 
                      start[0]+totalLength+1, start[1]+8, 
                      2.0, BLACK);
}

void Health::draw() const {
  IOManager::getInstance()
    .printMessageAt(title, start[0] - 10 * title.size(), start[1] - 4);
  drawBox();
  Draw_AALine(screen, start[0], start[1], 
                      start[0]+currentLength, start[1], 
                      thick, color);
}
void Health::update(Uint32 ticks) {
  deltaTime += ticks;
  if ( currentLength > 0 && deltaTime > interval ) {
    deltaTime = 0;
    currentLength -= increments;
  }
}

void Health::update2(Uint32 loss) {
  if (currentLength > loss)
    currentLength = currentLength - loss;
  else
    currentLength = 0;
}
