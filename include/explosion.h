#include <SDL2/SDL.h>

#ifndef EXPLOSION_H
#define EXPLOSION_H

class explosion
{
private:
  SDL_Rect dest; // sprite destination
  int time = 1;  // frame de l'explosion

public:
  explosion(SDL_Rect dest);

  // affiche l'explosion
  int afficher(SDL_Surface *win_src, SDL_Surface *win_dest);
};

#endif // EXPLOSION_H
