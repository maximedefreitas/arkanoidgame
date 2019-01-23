#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <cmath>

#include "ball.h"
#include "brick.h"
#include "vaisseau.h"
#include "bonus.h"
#include "hitbox.h"
#include "laser_beam.h"
#include "explosion.h"

#ifndef TERRAIN_H
#define TERRAIN_H

class terrain
{
private:
  // partie graphique
  SDL_Surface *window;
  SDL_Surface *sprite;
  int fond; // numero du fond a tracer

  std::vector<vaisseau *> vaisseaux;   // pointeur vers un vaisseau
  std::vector<ball *> balls;           // vecteur des balles
  std::vector<brick *> bricks;         // vecteur des briques
  std::vector<bonus *> bonus_malus;    // vecteur des bonus
  std::vector<laser_beam *> lasers;    // vecteur des laser (bonus)
  std::vector<explosion *> explosions; // vecteur des explosions

  int pts_per_frame = 0;    // points par frame
  int b_life_per_frame = 0; // vies supplementaire obtenue
  int lost = 0;             // indiquateur si il existe ou non des balles
  int bricks_left = 0;      // nombre de brique restante a casser
  int combo = 1;            // compteur de combo

  // methode prive de la classe
  // afficher des char avec la table ascii
  void afficher_ascii(int i, int j, SDL_Rect dest);

public:
  // constructeur
  terrain(SDL_Surface *win, SDL_Surface *spr, int fon, std::vector<vaisseau *> vai, std::vector<ball *>, std::vector<brick *>, int c);

  // destructeur
  ~terrain();

  // getteur
  int get_lost();
  SDL_Rect get_vaiss_pos(int pos);
  int get_bricks_left();

  // setteur
  void set_lost();
  void set_balls(ball *b);
  void move_init_ball(int num, ball_move bm);

  // deplacer le vaisseau
  void deplace_vaisseau(int i, int j, int lim);

  // mettre a jour le detecteur de click souris pour les bonus
  void set_click_souris();

  // tracer les elements a l'ecran
  // ou les supprimer si besoin
  void draw_all(int score, int life, int cylindrique);

  // calcule les collisions des prochains deplacements
  void collision_all(int cylindrique);

  // donne le nombre de point obtenus par frame
  int add_point();

  // donne le nombre de vie obtenus par frame
  int add_life();
};

#endif // TERRAIN_H
