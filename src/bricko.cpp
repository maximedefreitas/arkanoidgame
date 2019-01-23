#include "bricko.h"

bricko::bricko(SDL_Rect d)
{
  this->src2 = {32, 0, 32, 16};
  this->src = {192, 0, 32, 16};
  this->dest = d;
  this->hit_left = 2;
  this->bonus_container = 0;
  this->point = 5;
}
