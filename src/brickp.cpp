#include "brickp.h"

brickp::brickp(SDL_Rect d)
{
  this->src = {192, 64, 32, 16};
  this->src2 = {192, 48, 32, 16};
  this->src3 = {64, 16, 32, 16};
  this->dest = d;
  this->hit_left = 3;
  this->bonus_container = 0;
  this->point = 10;
}
