#include "bricka.h"

bricka::bricka(SDL_Rect d, int bonus)
{
  this->animation = 0;
  this->src = {0, 32, 32, 16};
  this->dest = d;
  this->hit_left = 1;
  this->bonus_container = bonus;
  this->point = 100;
}
