#include <SDL2/SDL.h>
#include <cmath>
#include <vector>
#include <iostream>

#define BONUS_TIME 300

#ifndef LASER_BEAM_H
#define LASER_BEAM_H

class laser_beam
{
private:
  SDL_Rect src = {17, 80, 12, 19}; // sprite origine
  SDL_Rect dest;                   // sprite destination
  double speedy = -15;             // vitesse des lasers
  int time_left = 1;               // si 0 supprimer l'objet

  // commun tous les lasers
  static int click_souris; //si 1, il y a eut un click de la souris
  static int timer_bonus;  //temps de l'effet du bonus restant

public:
  // constructeur
  laser_beam(int type, SDL_Rect d);

  // getteur
  int get_time_left();
  SDL_Rect get_dest();
  static int can_shoot();

  // setter
  static void next_frame();

  // mettre a jour le detecteur de click souris pour les bonus
  static void set_click_souris();
  static void reset_click_souris();
  void set_time_left_0();

  // affichage
  void affiche(SDL_Surface *win_src, SDL_Surface *win_dest);

  // animation des lasers
  void animation(int limite);

  // debut effet bonus laser beam
  static void start_laser_beam();
};

#endif // LASER_BEAM_H
