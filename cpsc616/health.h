#include "vector2f.h"
#include "ioManager.h"
#include "aaline.h"

class Health {
public:
  Health();
  Health(int sx, int sy, int tl, int cl,
         float t, int inc, Uint32 c, float sp, std::string _title);
  Health(int sx, int sy, int tl, std::string _title);
  void draw() const;
  void update(Uint32);
  void update2(Uint32 loss);
  void reset() { currentLength = totalLength; }
private:
  SDL_Surface* screen;
  Vector2f start;
  Uint32 totalLength;
  Uint32 currentLength;
  int thick;
  int increments;
  float interval;
  int deltaTime;
  const Uint32 RED;
  const Uint32 GRAY;
  const Uint32 BLACK;
  const Uint32 color;
  const std::string title;
  void drawBox() const;
  Health(const Health&);
  Health& operator=(const Health&);
};
