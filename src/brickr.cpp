#include "brickr.h"

brickr::brickr(SDL_Rect d)
{
  this->src3 = {192, 16, 32, 16};
  this->src2 = {0, 16, 32, 16};
  this->src = {128, 16, 32, 16};
  this->dest = d;
  this->hit_left = 3;
  this->bonus_container = 0;
  this->point = 10;
}
