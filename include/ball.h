#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>

#ifndef BALL_H
#define BALL_H

/*
permet de regrouper toutes les informations
pour decrire le mouvement de la balle
*/
struct ball_move
{
  double x;
  double y;
  double speedx;
  double speedy; // Toujours superieur en valeur abs a 1
};

class ball
{
private:
  SDL_Rect dest;     // sprite destination
  int taille;        // taille de la balle (1 a 6)
  ball_move current; // position et vitesse actuelle
  int lost = 0;      // indique si la balle est perdue

public:
  // Constructeur
  ball(int t, ball_move m);

  // Constructeur d'une nouvelle balle a partir d'une autre
  // avec un changement de la vitesse sur x en fonction d'un parametre
  ball(int param, ball *b);

  // getter
  ball_move get_ball_move();
  SDL_Rect get_hitbox();
  int get_taille();
  int get_lost();

  // setteur
  void set_lost();

  // afficher la balle
  void affiche(SDL_Surface *win_src, SDL_Surface *win_dest);

  // change le deplacement de la balle
  void modify_current(ball_move future);

  // multiplie la vitesse de la balle par un certain coeff si possible
  void speed_multiplier(double coeff);
};

#endif // BALL_H
