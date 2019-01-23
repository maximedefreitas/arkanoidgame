#include "brickb.h"

brickb::brickb(SDL_Rect d)
{
  this->src = {32, 16, 32, 16};
  this->dest = d;
  this->hit_left = 1;
  this->bonus_container = 0;
  this->point = 2;
}
