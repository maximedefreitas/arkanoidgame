#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>

#include "ball.h"

#ifndef HITBOX_H_INCLUDED
#define HITBOX_H_INCLUDED

// Permet de calculer l'aire de l'intersection de 2 rectangles
// definis par SDL_Rect
// renvoie 0 si l'intersection est nulle
int aire_intersection(SDL_Rect a, SDL_Rect b);

// modifie la structure ball_move future
// en fonction du type de rebond calcule
void rebond(SDL_Rect brick, ball *b, ball_move *future, int is_vaisseau);

#endif // HITBOX_H_INCLUDED
