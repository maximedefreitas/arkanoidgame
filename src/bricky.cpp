#include "bricky.h"

bricky::bricky(SDL_Rect d)
{
  this->src2 = {96, 16, 32, 16};
  this->src = {192, 32, 32, 16};
  this->dest = d;
  this->hit_left = 2;
  this->bonus_container = 0;
  this->point = 5;
}
