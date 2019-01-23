#include "vaisseau.h"

//fonction intermediaire
SDL_Rect taile_to_SDLRect_vaisseau(int taille)
{
  switch (taille)
  {
  case 1:
    return {384, 128, 64, 16};
  case 2:
    return {384, 144, 74, 16};
  case 3:
    return {384, 160, 82, 16};
  case 4:
    return {384, 176, 90, 16};
  case 5:
    return {384, 192, 98, 16};
  case 6:
    return {384, 208, 108, 16};
  case 7:
    return {384, 224, 118, 16};
  case 8:
    return {384, 240, 128, 16};
  default:
    return {384, 192, 98, 16};
  }
}

vaisseau::vaisseau(int t, SDL_Rect b)
{
  this->taille = t;
  this->dest = b;
}

SDL_Rect vaisseau::get_dest()
{
  return dest;
}

void vaisseau::deplace_vaisseau(int i, int lim)
{
  dest.x += i;
  if (dest.x + dest.w > lim)
    dest.x = lim - dest.w;
  if (dest.x < 0)
    dest.x = 0;
}

void vaisseau::affiche(SDL_Surface *win_src, SDL_Surface *win_dest)
{
  SDL_Rect src = taile_to_SDLRect_vaisseau(taille);
  SDL_BlitSurface(win_src, &src, win_dest, &dest);
}

void vaisseau::collision(ball *b, ball_move *future, int *combo)
{

  SDL_Rect balle = b->get_hitbox();
  balle.x = future->x;
  balle.y = future->y;

  if (aire_intersection(dest, balle) != 0)
  {
    rebond(dest, b, future, 1);
    (*combo) = 0;
  }
}

void vaisseau::change_size(int a)
{
  if (taille + a >= 1 && taille + a <= 8)
    taille += a;
}
