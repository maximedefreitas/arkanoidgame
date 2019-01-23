#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <cmath>

#include "ball.h"
#include "vaisseau.h"
#include "brick.h"
#include "terrain.h"
#include "bonus.h"
#include "game.h"

SDL_Window *game_window = nullptr;
SDL_Surface *game_window_surface = nullptr;
SDL_Surface *sprites_surface = nullptr;
game *current_game = nullptr;

// Variables de gestion du menu
int is_menu = 1;
int is_reset = 1;
int is_wrap = 0;
int nb_players = 1;
int pos_cursor = 1;

// Affiche un caractère ascii depuis la planche de sprite
void print_ascii(int i, int j, SDL_Rect dest)
{
  SDL_Rect src;
  src.x = 1 + i * 32;
  src.w = 15;
  src.y = 558 + j * 32;
  src.h = 20;
  SDL_BlitSurface(sprites_surface, &src, game_window_surface, &dest);
}

// Initialise la SDL
void init_SDL()
{
  game_window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 480, 600, SDL_WINDOW_SHOWN);
  game_window_surface = SDL_GetWindowSurface(game_window);

  sprites_surface = SDL_LoadBMP("./Arkanoid_sprites.bmp");
  SDL_SetColorKey(sprites_surface, true, 0); // 0: 00/00/00 noir -> transparent
}

// Initialise la partie
void init()
{
  // Creation d'une partie
  current_game = new game(is_wrap, nb_players);
  current_game->load(game_window_surface, sprites_surface);
}

// Met à jour la fenêtre si le joueur est dans une partie
void draw_game(int *is_menu)
{
  int status;
  // Afficher tout les elements
  current_game->get_terrain()->draw_all(current_game->get_score(), current_game->get_life(), current_game->get_cyl());
  // Affiche le score
  status = current_game->loop(is_menu);
  if (status == 1)
  {
    current_game->load(game_window_surface, sprites_surface);
  }
  else if (status == 2)
  {
    (*is_menu) = 1;
  }
  // Calcule des colisions et changement de vitesse et position des elements
  current_game->get_terrain()->collision_all(current_game->get_cyl());
}

// Met à jour la fenêtre si le joueur est sur le menu principal
void draw_menu(int nb_players, int is_wrap, int pos_cursor)
{
  int cursor_y;

  // Fond noir
  SDL_Rect src = {0, 525, 22, 15};
  SDL_Rect dest = {0, 0, 0, 0};
  for (int j = 0; j < game_window_surface->h; j += src.h)
  {
    for (int i = 0; i < game_window_surface->w; i += src.w)
    {
      dest.x = i;
      dest.y = j;
      SDL_BlitSurface(sprites_surface, &src, game_window_surface, &dest);
    }
  }

  // Logo "Arkanoid"
  src = {5, 430, 290, 80};
  dest = {(int)((game_window_surface->w - 290) / 2), 95, 290, 80};
  SDL_BlitSurface(sprites_surface, &src, game_window_surface, &dest);

  // Première option (nombre de joueurs)
  if (nb_players == 1)
  {
    print_ascii(12, 0, {(int)((game_window_surface->w - 180) / 2), 300, 15, 20});       // <
    print_ascii(1, 0, {(int)((game_window_surface->w - 180) / 2) + 30, 300, 15, 20});   // 1
    print_ascii(0, 2, {(int)((game_window_surface->w - 180) / 2) + 60, 300, 15, 20});   // P
    print_ascii(12, 1, {(int)((game_window_surface->w - 180) / 2) + 75, 300, 15, 20});  // L
    print_ascii(1, 1, {(int)((game_window_surface->w - 180) / 2) + 90, 300, 15, 20});   // A
    print_ascii(9, 2, {(int)((game_window_surface->w - 180) / 2) + 105, 300, 15, 20});  // Y
    print_ascii(5, 1, {(int)((game_window_surface->w - 180) / 2) + 120, 300, 15, 20});  // E
    print_ascii(2, 2, {(int)((game_window_surface->w - 180) / 2) + 135, 300, 15, 20});  // R
    print_ascii(14, 0, {(int)((game_window_surface->w - 180) / 2) + 165, 300, 15, 20}); // >
  }
  else
  {
    print_ascii(12, 0, {(int)((game_window_surface->w - 195) / 2), 300, 15, 20});       // <
    print_ascii(2, 0, {(int)((game_window_surface->w - 195) / 2) + 30, 300, 15, 20});   // 2
    print_ascii(0, 2, {(int)((game_window_surface->w - 195) / 2) + 60, 300, 15, 20});   // P
    print_ascii(12, 1, {(int)((game_window_surface->w - 195) / 2) + 75, 300, 15, 20});  // L
    print_ascii(1, 1, {(int)((game_window_surface->w - 195) / 2) + 90, 300, 15, 20});   // A
    print_ascii(9, 2, {(int)((game_window_surface->w - 195) / 2) + 105, 300, 15, 20});  // Y
    print_ascii(5, 1, {(int)((game_window_surface->w - 195) / 2) + 120, 300, 15, 20});  // E
    print_ascii(2, 2, {(int)((game_window_surface->w - 195) / 2) + 135, 300, 15, 20});  // R
    print_ascii(3, 2, {(int)((game_window_surface->w - 195) / 2) + 150, 300, 15, 20});  // S
    print_ascii(14, 0, {(int)((game_window_surface->w - 195) / 2) + 180, 300, 15, 20}); // >
  }

  // Deuxième option (plateau cylindrique)
  if (!is_wrap)
  {
    print_ascii(12, 0, {(int)((game_window_surface->w - 180) / 2), 360, 15, 20});       // <
    print_ascii(7, 2, {(int)((game_window_surface->w - 180) / 2) + 30, 360, 15, 20});   // W
    print_ascii(2, 2, {(int)((game_window_surface->w - 180) / 2) + 45, 360, 15, 20});   // R
    print_ascii(1, 1, {(int)((game_window_surface->w - 180) / 2) + 60, 360, 15, 20});   // A
    print_ascii(0, 2, {(int)((game_window_surface->w - 180) / 2) + 75, 360, 15, 20});   // P
    print_ascii(15, 3, {(int)((game_window_surface->w - 180) / 2) + 105, 360, 15, 20}); // o
    print_ascii(6, 3, {(int)((game_window_surface->w - 180) / 2) + 120, 360, 15, 20});  // f
    print_ascii(6, 3, {(int)((game_window_surface->w - 180) / 2) + 135, 360, 15, 20});  // f
    print_ascii(14, 0, {(int)((game_window_surface->w - 180) / 2) + 165, 360, 15, 20}); // >
  }
  else
  {
    print_ascii(12, 0, {(int)((game_window_surface->w - 165) / 2), 360, 15, 20});       // <
    print_ascii(7, 2, {(int)((game_window_surface->w - 165) / 2) + 30, 360, 15, 20});   // W
    print_ascii(2, 2, {(int)((game_window_surface->w - 165) / 2) + 45, 360, 15, 20});   // R
    print_ascii(1, 1, {(int)((game_window_surface->w - 165) / 2) + 60, 360, 15, 20});   // A
    print_ascii(0, 2, {(int)((game_window_surface->w - 165) / 2) + 75, 360, 15, 20});   // P
    print_ascii(15, 3, {(int)((game_window_surface->w - 165) / 2) + 105, 360, 15, 20}); // o
    print_ascii(14, 3, {(int)((game_window_surface->w - 165) / 2) + 120, 360, 15, 20}); // n
    print_ascii(14, 0, {(int)((game_window_surface->w - 165) / 2) + 150, 360, 15, 20}); // >
  }

  // Affichage du curseur
  if (pos_cursor == 1)
    cursor_y = 303;
  else
    cursor_y = 363;
  src = {384, 128, 64, 16};
  dest = {(int)((game_window_surface->w - 195) / 2) - 74, cursor_y, 64, 16};
  SDL_BlitSurface(sprites_surface, &src, game_window_surface, &dest);

  // Deuxième curseur si le joueur choisit l'option 2 joueurs
  if (nb_players == 2)
  {
    dest = {(int)((game_window_surface->w - 195) / 2) + 205, cursor_y, 64, 16};
    SDL_BlitSurface(sprites_surface, &src, game_window_surface, &dest);
  }
  return;
}

int main(int argc, char **argv)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    std::cerr << "Echec de l'initialisation de la SDL" << SDL_GetError() << std::endl;
    return 1;
  }

  init_SDL();
  bool quit = false;
  SDL_Event event;

  while (!quit)
  {
    // Si le joueur est dans le menu:
    if (is_menu)
    {
      is_reset = 1;

      while (!quit && SDL_PollEvent(&event))
      {
        switch (event.type)
        {
        case SDL_QUIT:
          quit = true;
          break;
        case SDL_KEYDOWN: // Touche clavier
          switch (event.key.keysym.sym)
          {
          case SDLK_LEFT:  // Flèche gauche
          case SDLK_RIGHT: // Flèche droite
            if (pos_cursor == 1)
            {
              if (nb_players == 1)
                nb_players = 2;
              else
                nb_players = 1;
            }
            else
            {
              if (is_wrap)
                is_wrap = 0;
              else
                is_wrap = 1;
            }
            break;
          case SDLK_UP:   // Flèche haut
          case SDLK_DOWN: // Flèche bas
            if (pos_cursor == 1)
              pos_cursor = 2;
            else
              pos_cursor = 1;
            break;
          case SDLK_RETURN: // Entrée
            is_menu = 0;
            break;
          case SDLK_ESCAPE: // Echap
            quit = true;
            break;
          default:
            break;
          }
          break; default : break;
        }
      }

      draw_menu(nb_players, is_wrap, pos_cursor);

      SDL_UpdateWindowSurface(game_window);
      SDL_Delay(20); // 50 fps
    }

    // Sinon, il est dans une partie:
    else
    {
      if (is_reset == 1)
      {
        init();
        is_reset = 0;
      }

      while (!quit && SDL_PollEvent(&event))
      {
        switch (event.type)
        {
        case SDL_QUIT:
          quit = true;
          break;
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym)
          {
          case SDLK_LEFT:
            if (nb_players == 2)
            {
              current_game->get_terrain()->deplace_vaisseau(1, -10, game_window_surface->w);
            }
            break;
          case SDLK_RIGHT:
            if (nb_players == 2)
            {
              current_game->get_terrain()->deplace_vaisseau(1, 10, game_window_surface->w);
            }
            break;
          case SDLK_PAGEDOWN: // Raccourci pour passer un niveau
            current_game->next_level(game_window_surface, sprites_surface);
            break;
          case SDLK_ESCAPE:
            quit = true;
            break;
          default:
            break;
          }
          break;
        case SDL_MOUSEMOTION:
          current_game->get_terrain()->deplace_vaisseau(0, event.motion.xrel, game_window_surface->w);
          break;
        case SDL_MOUSEBUTTONDOWN:
          current_game->get_terrain()->set_click_souris();
          current_game->set_click();
          break;
        default:
          break;
        }
      }

      draw_game(&is_menu);

      SDL_UpdateWindowSurface(game_window);
      SDL_Delay(20); // 50 fps
    }
  }

  SDL_Quit();
  return 0;
}
