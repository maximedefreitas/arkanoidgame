#include "laser_beam.h"

// initialisation variables statics
int laser_beam::click_souris = 0;
int laser_beam::timer_bonus = 0;

laser_beam::laser_beam(int type, SDL_Rect d)
{
  SDL_Rect rect = d;
  if (type != 0)
    rect.x = d.x + d.w - src.w;
  this->dest = rect;
}

int laser_beam::get_time_left()
{
  return time_left;
}

SDL_Rect laser_beam::get_dest()
{
  return dest;
}

int laser_beam::can_shoot()
{
  if (click_souris == 1 && timer_bonus > 0)
    return 1;
  else
    return 0;
}

void laser_beam::next_frame()
{
  //temps restant avant fin bonus
  if (timer_bonus > 0)
    timer_bonus--;
}

void laser_beam::set_click_souris()
{
  click_souris = 1;
}

void laser_beam::reset_click_souris()
{
  click_souris = 0;
}

void laser_beam::set_time_left_0()
{
  time_left = 0;
}

void laser_beam::affiche(SDL_Surface *win_src, SDL_Surface *win_dest)
{
  SDL_BlitSurface(win_src, &src, win_dest, &dest);
}

void laser_beam::animation(int limite)
{
  //chute
  dest.y += floor(speedy);

  //depasser la limite
  if (dest.y < limite - 50)
    time_left = 0;
}

void laser_beam::start_laser_beam()
{
  timer_bonus = BONUS_TIME;
}
