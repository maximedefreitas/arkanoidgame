#include "brick.h"
#include "hitbox.h"

#define signof(a) ((a) / abs((a)))

int brick::get_hit_left()
{
  return hit_left;
}

int brick::get_bonus_container()
{
  return bonus_container;
}
SDL_Rect brick::get_dest()
{
  return dest;
}

int brick::get_point()
{
  return point;
}

int brick::get_breakable()
{
  return breakable;
}

void brick::affiche(SDL_Surface *win_src, SDL_Surface *win_dest)
{
  if (animation == -1)
  {
    switch (hit_left)
    {
    case 3:
      SDL_BlitSurface(win_src, &src3, win_dest, &dest);
      break;
    case 2:
      SDL_BlitSurface(win_src, &src2, win_dest, &dest);
      break;
    default:
      SDL_BlitSurface(win_src, &src, win_dest, &dest);
    }
  }
  else
  {
    src.x = floor(animation / 6) * 32;
    SDL_BlitSurface(win_src, &src, win_dest, &dest);
    animation = (animation + 1) % 36;
  }
}

int brick::collision(ball *b, ball_move *future)
{

  SDL_Rect balle = b->get_hitbox();
  balle.x = future->x;
  balle.y = future->y;

  if (aire_intersection(dest, balle) != 0)
  {
    rebond(dest, b, future, 0);
    if (hit_left >= 0)
      this->hit_left--;
    return 1;
  }

  return 0;
}

void brick::take_hit()
{
  this->hit_left--;
}
