#include "brickw.h"

brickw::brickw(SDL_Rect d)
{
  this->src = {0, 0, 32, 16};
  this->dest = d;
  this->bonus_container = 7;
  this->point = 10000;
  this->breakable = 0;
}
