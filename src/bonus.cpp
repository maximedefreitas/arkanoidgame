#include "bonus.h"

#define SLOW_DOWN 1
#define CATCH_FIRE 2
#define EXPAND 3
#define DIVIDE 4
#define LASER_BEAM 5
#define BREAK 6
#define PLAYER_ADDITION 7
#define SPEED_UP 8
#define REDUCE 9

// permet de recuperer le sprite correspondant au bonus
SDL_Rect get_sprite(int type_bonus)
{
  switch (type_bonus)
  {
  case SLOW_DOWN:
    return {256, 0, 32, 14};
  case CATCH_FIRE:
    return {256, 16, 32, 14};
  case EXPAND:
    return {256, 48, 32, 14};
  case DIVIDE:
    return {256, 64, 32, 14};
  case LASER_BEAM:
    return {256, 32, 32, 14};
  case BREAK:
    return {256, 80, 32, 14};
  case PLAYER_ADDITION:
    return {256, 96, 32, 14};
  case SPEED_UP:
    return {256, 385, 32, 14};
  case REDUCE:
    return {256, 400, 32, 14};
  default:
    return {256, 0, 32, 14};
  }
}

bonus::bonus(int type, SDL_Rect d)
{
  this->src = get_sprite(type);
  this->type_bonus = type;
  this->dest = d;
}

int bonus::get_time_left()
{
  return time_left;
}

SDL_Rect bonus::get_dest()
{
  return dest;
}

void bonus::affiche(SDL_Surface *win_src, SDL_Surface *win_dest)
{
  SDL_BlitSurface(win_src, &src, win_dest, &dest);
}

void bonus::animation(int limite)
{
  //changement de sprite
  if (animation_timer == 0)
  {
    if (src.x == 480)
      src.x = 256;
    else
      src.x += 32;
  }
  animation_timer = (animation_timer + 1) % 5;

  //chute
  dest.y += floor(speedy);

  //depasser la limite
  if (dest.y > limite + 50)
    time_left = 0;
}

void bonus::action_bonus(std::vector<ball *> *balls, vaisseau *v, int *b_life)
{
  switch (type_bonus)
  {
  //reduit la vitesse des balles de 20%
  case SLOW_DOWN:
    for (std::vector<ball *>::iterator b = balls->begin(); b != balls->end(); ++b)
      (*b)->speed_multiplier(0.8);
    break;

  //augmente la vitesse des balles de 25%
  case SPEED_UP:
    for (std::vector<ball *>::iterator b = balls->begin(); b != balls->end(); ++b)
      (*b)->speed_multiplier(1.25);
    break;

  //augmente la taille du vaisseau si possible
  case EXPAND:
    v->change_size(1);
    break;

  //diminue la taille du vaisseau si possible
  case REDUCE:
    v->change_size(-1);
    break;

  //divise toutes les balles en 2
  //limite de 10 balles sur le terrain
  case DIVIDE:
  {
    std::vector<ball *>::iterator it_end = balls->end();
    for (std::vector<ball *>::iterator b = balls->begin(); b != it_end; ++b)
    {
      if (balls->size() < 10)
        balls->push_back(new ball(1, *b));
    }
  }
  break;

  case PLAYER_ADDITION:
    (*b_life)++;
    break;

  case LASER_BEAM:
    laser_beam::start_laser_beam();
    break;
  }
}
