#include "explosion.h"

SDL_Rect time_to_SDLRect_explosion(int t)
{
  switch (t)
  {
  case 1:
    return {0, 384, 32, 32};
  case 2:
    return {32, 384, 32, 32};
  case 3:
    return {64, 384, 32, 32};
  case 4:
    return {96, 384, 32, 32};
  case 5:
    return {128, 384, 32, 32};
  default:
    return {160, 384, 32, 32};
  }
}

explosion::explosion(SDL_Rect d)
{
  this->dest = d;
}

int explosion::afficher(SDL_Surface *win_src, SDL_Surface *win_dest)
{
  if (time < 7)
  {
    SDL_Rect src = time_to_SDLRect_explosion(time);
    SDL_BlitSurface(win_src, &src, win_dest, &dest);
    time++;
    return 0;
  }

  return 1;
}
