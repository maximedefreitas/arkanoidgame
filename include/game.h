#include <fstream>
#include <string>

#include "ball.h"
#include "vaisseau.h"
#include "brick.h"
#include "bricko.h"
#include "brickc.h"
#include "brickr.h"
#include "brickp.h"
#include "bricky.h"
#include "brickg.h"
#include "brickb.h"
#include "bricka.h"
#include "brickd.h"
#include "brickw.h"
#include "terrain.h"
#include "bonus.h"

#ifndef GAME_H
#define GAME_H

class game
{
private:
  int score;           // score total de la partie
  int life;            // nb de vie restante
  terrain *niveau;     // niveau en cours
  int cylindre;        // mode de jeu cylindrique
  int num_terrain = 1; // num du terrain actuel
  int nb_joueur;       // nb de joueur

  // variables pour lancer la premiere balle
  int transition = 1; // variable a 1 si etat de transition
  int click = 0;      // variable detection de click

public:
  game(int cyl, int nb_joueur);

  ~game();

  // getteur
  int get_score();
  int get_life();
  int get_cyl();
  terrain *get_terrain();

  // setteur
  void set_click();
  void load(SDL_Surface *win, SDL_Surface *spr);

  // affiche le score
  int loop(int *menu);

  // passe le niveau
  void next_level(SDL_Surface *win, SDL_Surface *spr);
};

#endif // GAME_H
