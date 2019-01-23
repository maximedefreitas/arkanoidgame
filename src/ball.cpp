#include "ball.h"

//fonctions intermediaires
SDL_Rect taile_to_SDLRect_ball(int taille)
{
  switch (taille)
  {
  case 1:
    return {4, 69, 8, 6};
  case 2:
    return {19, 68, 10, 8};
  case 3:
    return {34, 68, 12, 10};
  case 4:
    return {49, 67, 14, 10};
  case 5:
    return {64, 66, 16, 12};
  case 6:
    return {79, 66, 18, 12};
  default:
    return {49, 67, 14, 10};
  }
}

ball::ball(int t, ball_move m)
{
  this->taille = t;
  this->dest = taile_to_SDLRect_ball(t);
  this->dest.x = round(m.x);
  this->dest.y = round(m.y);
  this->current = m;
}

ball::ball(int param, ball *b)
{
  this->taille = b->get_taille();
  this->dest = b->get_hitbox();
  this->current = b->get_ball_move();

  this->current.speedy = -current.speedy;
  if (param)
  {
    this->current.speedx = -current.speedx;
  }
}

ball_move ball::get_ball_move()
{
  return current;
}

SDL_Rect ball::get_hitbox()
{
  return dest;
}

int ball::get_taille()
{
  return taille;
}

int ball::get_lost()
{
  return lost;
}

void ball::set_lost()
{
  lost = 1;
}

void ball::affiche(SDL_Surface *win_src, SDL_Surface *win_dest)
{
  SDL_Rect src = taile_to_SDLRect_ball(taille);
  dest.x = round(current.x);
  dest.y = round(current.y);
  SDL_BlitSurface(win_src, &src, win_dest, &dest);
}

void ball::modify_current(ball_move future)
{
  current = future;
}

void ball::speed_multiplier(double coeff)
{
  if (abs(current.speedx * coeff) >= 1)
    current.speedx *= coeff;
  else
  {
    if (current.speedx > 0)
      current.speedx = 1;
    else
      current.speedx = -1;
  }

  // speedy superieur a 1 en valeur absolue
  if (abs(current.speedy * coeff) >= 1)
    current.speedy *= coeff;
  else
  {
    if (current.speedy > 0)
      current.speedy = 1;
    else
      current.speedy = -1;
  }
}
