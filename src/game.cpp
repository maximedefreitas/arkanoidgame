#include "ball.h"
#include "game.h"

#define SCORE_LIM 1000000
#define LIFE_LIM 10

game::game(int cyl, int nj)
{
  this->score = 0;
  this->life = 3;
  this->cylindre = cyl;
  this->nb_joueur = nj;
}

game::~game()
{
  delete niveau;
}

int game::get_score()
{
  return score;
}

terrain *game::get_terrain()
{
  return niveau;
}

int game::get_life()
{
  return life;
}

int game::get_cyl()
{
  return cylindre;
}

void game::set_click()
{
  click = 1;
}

void game::load(SDL_Surface *win, SDL_Surface *spr)
{
  // compteur de briques
  int c = 0;

  // creation du vaisseau
  std::vector<vaisseau *> v;
  v.push_back(new vaisseau(2, {win->w / 4 - 16, win->h - 26, 90, 16}));
  if (nb_joueur == 2)
  {
    v.push_back(new vaisseau(2, {3 * win->w / 4 - 16, win->h - 26, 90, 16}));
  }

  // initialisation de la balle
  std::vector<ball *> balls;
  balls.push_back(new ball(4, {(double)win->w / 2, double(600 - 50), 0, 0}));

  // initialisation brique
  std::vector<brick *> bricks;
  std::string line;
  std::ifstream level("levels/" + std::to_string(num_terrain) + ".txt");
  if (level.is_open())
  {
    for (int j = 0; j < 15; j++)
    {
      for (int i = 0; i < 15; i++)
      {
        getline(level, line);

        if (line == "P")
        {
          bricks.push_back(new brickp({i * 32, j * 16 + 25, 32, 16}));
          c++;
        }
        else if (line == "R")
        {
          bricks.push_back(new brickr({i * 32, j * 16 + 25, 32, 16}));
          c++;
        }
        else if (line == "O")
        {
          bricks.push_back(new bricko({i * 32, j * 16 + 25, 32, 16}));
          c++;
        }
        else if (line == "Y")
        {
          bricks.push_back(new bricky({i * 32, j * 16 + 25, 32, 16}));
          c++;
        }
        else if (line == "G")
        {
          bricks.push_back(new brickg({i * 32, j * 16 + 25, 32, 16}));
          c++;
        }
        else if (line == "C")
        {
          bricks.push_back(new brickc({i * 32, j * 16 + 25, 32, 16}));
          c++;
        }
        else if (line == "B")
        {
          bricks.push_back(new brickb({i * 32, j * 16 + 25, 32, 16}));
          c++;
        }
        else if (line == "W")
        {
          bricks.push_back(new brickw({i * 32, j * 16 + 25, 32, 16}));
        }
        else if (line == "D")
        {
          bricks.push_back(new brickd({i * 32, j * 16 + 25, 32, 16}));
        }
        else if (line == "E")
        {
          ;
        }
        else
        {
          bricks.push_back(new bricka({i * 32, j * 16 + 25, 32, 16}, stoi(line)));
        }
      }
    }
  }

  niveau = new terrain(win, spr, num_terrain % 6, v, balls, bricks, c);
}

int game::loop(int *menu)
{

  //recuperation position du vaisseau
  SDL_Rect vaiss_pos = niveau->get_vaiss_pos(0);

  if (niveau->get_lost())
  {
    life--;
    niveau->set_lost();
    if (life <= 0)
    {
      (*menu) = 1;
    }
    else
    {
      niveau->set_balls(new ball(4, {(double)(vaiss_pos.x + vaiss_pos.w / 2 - 7), (double)(vaiss_pos.y - 10), 0, 0}));
      transition = 1;
      click = 0;
    }
  }

  if (transition)
  {
    if (!click)
    {
      niveau->move_init_ball(0, {(double)(vaiss_pos.x + vaiss_pos.w / 2 - 7), (double)(vaiss_pos.y - 10), 0, 0});
    }
    else
    {
      niveau->move_init_ball(0, {(double)(vaiss_pos.x + vaiss_pos.w / 2 - 7), (double)(vaiss_pos.y - 10), (double)(5 + 5 * (num_terrain - 1) / 8), (double)(10 + 10 * (num_terrain) / 8)});
      transition = 0;
    }
  }

  score = (score + niveau->add_point()) % SCORE_LIM;

  life = (life + niveau->add_life());
  if (life > 3)
  {
    score += (life - 3) * 1000;
    life = 3;
  }

  //passage au niveau suivant
  if (niveau->get_bricks_left() == 0)
  {
    num_terrain++;
    click = 0;
    transition = 1;
    if (num_terrain >= 9)
    {
      return 2;
    }
    return 1;
  }

  return 0;
}

void game::next_level(SDL_Surface *win, SDL_Surface *spr)
{
  num_terrain++;
  transition = 1;
  click = 0;
  load(win, spr);
}
