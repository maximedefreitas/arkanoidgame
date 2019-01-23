#include "brickd.h"

brickd::brickd(SDL_Rect d)
{
  this->animation = 0;
  this->src = {0, 48, 32, 16};
  this->dest = d;
  this->hit_left = 1;
  this->bonus_container = 7;
  this->point = 100;
}
