#ifndef VAISSEAU_H
#define VAISSEAU_H

#include "ball.h"
#include "hitbox.h"

class vaisseau
{
private:
  SDL_Rect src;  // sprite
  SDL_Rect dest; // position

  int taille;

public:
  // constructeur
  vaisseau(int t, SDL_Rect b);

  // getteur
  SDL_Rect get_dest();

  // deplacement du vaisseau
  void deplace_vaisseau(int i, int lim);

  // affichage
  void affiche(SDL_Surface *win_src, SDL_Surface *win_dest);

  // collision
  void collision(ball *b, ball_move *future, int *combo);

  // augmente ou reduit la taille du vaisseau
  void change_size(int a);
};

#endif // VAISSEAU_H
