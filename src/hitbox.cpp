#include "hitbox.h"

int aire_intersection(SDL_Rect a, SDL_Rect b)
{
  //intersection des deux
  int bas = std::min(a.y + a.h, b.y + b.h);
  int haut = std::max(a.y, b.y);
  int gauche = std::max(a.x, b.x);
  int droite = std::min(a.x + a.w, b.x + b.w);

  if (bas > haut && gauche < droite)
    return ((bas - haut) * (droite - gauche));
  else
    return 0;
}

void rebond(SDL_Rect brick, ball *b, ball_move *future, int is_vaisseau)
{
  SDL_Rect ball = b->get_hitbox();
  ball.x = future->x;
  ball.y = future->y;

  SDL_Rect ball_gauche = ball, ball_droite = ball,
           ball_haut = ball, ball_bas = ball;

  ball_gauche.w = 1;
  ball_droite.w = 1;
  ball_droite.x = (ball.x + ball.w - 1);
  ball_haut.h = 1;
  ball_bas.h = 1;
  ball_bas.y = (ball.y + ball.h - 1);

  int ig = aire_intersection(brick, ball_gauche);
  int ih = aire_intersection(brick, ball_haut);
  int id = aire_intersection(brick, ball_droite);
  int ib = aire_intersection(brick, ball_bas);

  // rebond vaisseau
  if (is_vaisseau)
  {
    if (std::max(ig, id) <= std::max(ih, ib))
    {
      int balle_centre = std::round(ball.x + ball.w / 2);

      // decoupage en 3 zones
      // centre
      if ((balle_centre >= brick.x + 1 * brick.w / 3) && (balle_centre <= brick.x + 2 * brick.w / 3))
      {
        future->speedy = -future->speedy;
      }
      // gauche
      else if (balle_centre <= brick.x + 1 * brick.w / 3)
      {
        double vitessex = future->speedx;
        future->speedx = -abs(future->speedy);
        future->speedy = -abs(vitessex);
      }
      // droite
      else
      {
        double vitessex = future->speedx;
        future->speedx = abs(future->speedy);
        future->speedy = -abs(vitessex);
      }
    }
    // cas des cotes
    else
    {
      future->speedx = -future->speedx;
      future->speedy = -future->speedy;
    }
  }
  // rebond classique
  else
  {
    if (std::max(ig, id) >= std::max(ih, ib))
      future->speedx = -future->speedx;
    else
      future->speedy = -future->speedy;
  }
}
