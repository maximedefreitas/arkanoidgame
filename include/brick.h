#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>

#include "ball.h"
#include "bonus.h"

#ifndef BRICK_H
#define BRICK_H

class brick
{
protected:
  // sprites
  SDL_Rect src;
  SDL_Rect src2;
  SDL_Rect src3;
  SDL_Rect dest; // position

  int breakable = 1;   // 0 si incassable
  int hit_left = 0;    // coup restant avant casse
  int bonus_container; // type de bonus contenu sinon 0
  int point;           // point gagne en cassant la brique
  int animation = -1;  // variable pour animation des bricks (-1 si pas animation)

public:
  // getteur
  int get_hit_left();
  int get_bonus_container();
  SDL_Rect get_dest();
  int get_point();
  int get_breakable();

  // affichage
  void affiche(SDL_Surface *win_src, SDL_Surface *win_dest);

  // collision
  int collision(ball *b, ball_move *future);
  void take_hit();
};

#endif // BRICK_H
