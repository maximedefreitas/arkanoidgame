#include "brickg.h"

brickg::brickg(SDL_Rect d)
{
  this->src = {96, 0, 32, 16};
  this->dest = d;
  this->hit_left = 1;
  this->bonus_container = 0;
  this->point = 2;
}
