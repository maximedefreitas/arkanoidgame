#include <SDL2/SDL.h>
#include <cmath>
#include <vector>

#include "ball.h"
#include "vaisseau.h"
#include "laser_beam.h"

#ifndef BONUS_H
#define BONUS_H

class bonus
{
private:
  SDL_Rect src;  // sprite origine
  SDL_Rect dest; // sprite destination
  int type_bonus;
  int animation_timer = 1; // variable pour animation sprite
  double speedy = 5;       // vitesse de chute du bonus
  int time_left = 1;       // si 0 supprimer l'objet

public:
  // constructeur
  bonus(int type, SDL_Rect d);

  // getteur
  int get_time_left();
  SDL_Rect get_dest();

  // affichage
  void affiche(SDL_Surface *win_src, SDL_Surface *win_dest);

  // animation du bonus
  void animation(int limite);

  // action du bonus
  void action_bonus(std::vector<ball *> *balls, vaisseau *v, int *b_life);
};

#endif // BONUS_H
