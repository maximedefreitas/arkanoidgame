#include "terrain.h"

void terrain::afficher_ascii(int i, int j, SDL_Rect dest)
{
  SDL_Rect src;
  src.x = 1 + i * 32;
  src.y = 558 + j * 32;
  src.w = 15;
  src.h = 20;
  SDL_BlitSurface(sprite, &src, window, &dest);
}

terrain::terrain(SDL_Surface *win, SDL_Surface *spr, int fon, std::vector<vaisseau *> vai, std::vector<ball *> bal, std::vector<brick *> bri, int c)
{
  this->window = win;
  this->sprite = spr;
  this->fond = fon;
  this->vaisseaux = vai;
  this->balls = bal;
  this->bricks = bri;
  this->bricks_left = c;
}

terrain::~terrain()
{
  for (std::vector<vaisseau *>::iterator v = vaisseaux.end(); v != vaisseaux.begin(); --v)
    delete (*v); // le vaisseau
  for (std::vector<ball *>::iterator b = balls.end(); b != balls.begin(); --b)
    delete (*b); // les balles
  for (std::vector<brick *>::iterator b = bricks.end(); b != bricks.begin(); --b)
    delete (*b); // les briques
  for (std::vector<bonus *>::iterator b = bonus_malus.end(); b != bonus_malus.begin(); --b)
    delete (*b); // les bonus
  for (std::vector<laser_beam *>::iterator b = lasers.end(); b != lasers.begin(); --b)
    delete (*b); // les lasers
  for (std::vector<explosion *>::iterator b = explosions.end(); b != explosions.begin(); --b)
    delete (*b); // les explosions
}

int terrain::get_lost()
{
  return lost;
}

SDL_Rect terrain::get_vaiss_pos(int pos)
{
  return vaisseaux.at(pos)->get_dest();
}

int terrain::get_bricks_left()
{
  return bricks_left;
}

void terrain::set_lost()
{
  lost = 0;
}

void terrain::set_balls(ball *b)
{
  balls.push_back(b);
}

void terrain::move_init_ball(int num, ball_move bm)
{
  balls.at(num)->modify_current(bm);
}

void terrain::deplace_vaisseau(int num_joueur, int i, int lim)
{
  vaisseaux.at(num_joueur)->deplace_vaisseau(i, lim);
}

void terrain::set_click_souris()
{
  laser_beam::set_click_souris();
}

void terrain::draw_all(int score, int life, int cylindrique)
{
  SDL_Rect src_fond;
  SDL_Rect dest;

  //choisir la source pour le fond
  switch (fond)
  {
  case 0:
    src_fond = {0, 128, 48, 64};
    break;
  case 1:
    src_fond = {64, 128, 64, 64};
    break;
  case 2:
    src_fond = {128, 128, 64, 64};
    break;
  case 3:
    src_fond = {192, 128, 64, 64};
    break;
  case 4:
    src_fond = {256, 128, 64, 64};
    break;
  case 5:
    src_fond = {320, 128, 64, 64};
    break;
  default:
    src_fond = {0, 128, 48, 64};
  }

  //remplir le fond
  dest = {0, 0, 0, 0};
  for (int j = 0; j < window->h; j += src_fond.h)
  {
    for (int i = 0; i < window->w; i += src_fond.w)
    {
      dest.x = i;
      dest.y = j;
      SDL_BlitSurface(sprite, &src_fond, window, &dest);
    }
  }

  //affiche les vaisseaux
  for (std::vector<vaisseau *>::iterator v = vaisseaux.begin(); v != vaisseaux.end(); ++v)
  {
    (*v)->affiche(sprite, window);
  }

  //affiche les briques ou les enleve du vecteur bricks
  for (std::vector<brick *>::iterator b = bricks.begin(); b != bricks.end(); ++b)
  {
    if (((*b)->get_hit_left()) <= 0 && (*b)->get_breakable())
    {

      if ((*b)->get_bonus_container() != 0)
      {
        bonus_malus.push_back(new bonus((*b)->get_bonus_container(), (*b)->get_dest()));
        bricks_left++;
      }
      pts_per_frame += (*b)->get_point();
      delete *b;
      b = bricks.erase(b);
      b--;
      bricks_left--;
    }
    else
      (*b)->affiche(sprite, window);
  }

  //affiche les bonus ou les enleve du vecteur
  for (std::vector<bonus *>::iterator b = bonus_malus.begin(); b != bonus_malus.end(); ++b)
  {
    if (((*b)->get_time_left()) <= 0)
    {
      delete (*b);
      b = bonus_malus.erase(b);
      b--;
    }
    else
      (*b)->affiche(sprite, window);
  }

  //affiche les lasers, les ajoute ou les enleve du vecteur
  if (laser_beam::can_shoot())
  {
    //vaisseau 1
    lasers.push_back(new laser_beam(0, vaisseaux.at(0)->get_dest()));
    lasers.push_back(new laser_beam(1, vaisseaux.at(0)->get_dest()));
    //vaisseau 2
    if (vaisseaux.size() == 2)
    {
      lasers.push_back(new laser_beam(0, vaisseaux.at(1)->get_dest()));
      lasers.push_back(new laser_beam(1, vaisseaux.at(1)->get_dest()));
    }
  }

  laser_beam::reset_click_souris();
  for (std::vector<laser_beam *>::iterator l = lasers.begin(); l != lasers.end(); ++l)
  {
    if (((*l)->get_time_left()) <= 0)
    {
      delete (*l);
      l = lasers.erase(l);
      l--;
    }
    else
      (*l)->affiche(sprite, window);
  }
  laser_beam::next_frame();

  //remplir le fond
  dest = {0, 0, 22, 25};
  src_fond = {0, 520, 22, 25};
  for (int i = 0; i < window->w; i += src_fond.w)
  {
    dest.x = i;
    SDL_BlitSurface(sprite, &src_fond, window, &dest);
  }

  //afficher le score
  afficher_ascii(3, 2, {10, 1, 15, 20});
  afficher_ascii(3, 3, {25, 1, 15, 20});
  afficher_ascii(15, 3, {40, 1, 15, 20});
  afficher_ascii(2, 4, {55, 1, 15, 20});
  afficher_ascii(5, 3, {70, 1, 15, 20});
  afficher_ascii(10, 0, {85, 1, 15, 20});

  int n;
  src_fond = {1, 558, 15, 20};
  dest = {100, 1, 15, 20};
  for (int i = 5; i >= 0; i--)
  {
    n = (int)std::floor(score / std::pow(10, i));
    src_fond.x = 1 + n * 32;
    SDL_BlitSurface(sprite, &src_fond, window, &dest);
    dest.x += 15;
    score = score - n * (std::pow(10, i));
  }

  //afficher nb de vie
  src_fond = {384, 128, 64, 16};
  dest = {window->w - 70, 5, 64, 16};
  SDL_BlitSurface(sprite, &src_fond, window, &dest);
  afficher_ascii(8, 4, {window->w - 90, 1, 15, 20});
  afficher_ascii(life, 0, {window->w - 110, 1, 15, 20});

  //affiche la ou les explosions ou les enleve du vecteur explosion
  for (std::vector<explosion *>::iterator b = explosions.begin(); b != explosions.end(); ++b)
  {
    if ((*b)->afficher(sprite, window))
    {
      delete (*b);
      b = explosions.erase(b);
      b--;
    }
  }

  //affiche la ou les balles ou les enleve du vecteur ball
  for (std::vector<ball *>::iterator b = balls.begin(); b != balls.end(); ++b)
  {
    if ((*b)->get_lost())
    {
      dest = (*b)->get_hitbox();
      dest.y = (window->h) - 32;
      dest.w = 0;
      dest.h = 0;
      explosions.push_back(new explosion(dest));
      delete *b;
      b = balls.erase(b);
      //si plus de balle dans le vector, vie en moins
      if (balls.size() != 0)
        b--;
      else
      {
        lost = 1;
        return;
      }
    }
    else
      (*b)->affiche(sprite, window);
  }
}

void terrain::collision_all(int cylindrique)
{

  //deplacement ou colission des bonus
  for (std::vector<bonus *>::iterator b = bonus_malus.begin(); b != bonus_malus.end(); ++b)
  {
    //vaisseau
    if (aire_intersection((*b)->get_dest(), vaisseaux.at(0)->get_dest()) != 0)
    {
      (*b)->action_bonus(&balls, vaisseaux.at(0), &b_life_per_frame);
      delete *b;
      b = bonus_malus.erase(b);
      b--;
    }
    else
      (*b)->animation(window->h);

  }

  //deplacement ou colission des lasers
  for (std::vector<laser_beam *>::iterator l = lasers.begin(); l != lasers.end(); ++l)
  {
    //collision avec les bricks
    for (std::vector<brick *>::iterator bri = bricks.begin(); bri != bricks.end(); ++bri)
    {
      if (aire_intersection((*l)->get_dest(), (*bri)->get_dest()) != 0)
      {
        (*bri)->take_hit();
        (*l)->set_time_left_0();
      }
    }
    (*l)->animation(50);
  }

  //calcul pour toutes les balles
  for (std::vector<ball *>::iterator b = balls.begin(); b != balls.end(); ++b)
  {

    //future deplacement de la balle
    ball_move future = (*b)->get_ball_move();

    int current_speedx = future.speedx;
    int current_speedy = future.speedy;
    double max_speed_dir = std::max(abs(current_speedx), abs(current_speedy));

    for (int i = 0; i < max_speed_dir; i++)
    {

      //collison avec les bords
      if (cylindrique)
      {
        if (future.x < 1)
        {
          future.x = window->w;
          combo++;
        }
        else if (future.x > (window->w))
        {
          future.x = 1;
          combo++;
        }
      }
      else
      {
        if ((future.x < 1) || (future.x + (*b)->get_hitbox().w > (window->w)))
        {
          future.speedx = -future.speedx;
          combo++;
        }
      }
      if (future.y < 1 + 25)
      {
        future.speedy = -future.speedy;
        combo++;
      }

      //balle perdu
      if (future.y > (window->h) - 10)
        (*b)->set_lost();

      // collision avec le vaisseau
      for (std::vector<vaisseau *>::iterator v = vaisseaux.begin(); v != vaisseaux.end(); ++v)
      {
        (*v)->collision((*b), &future, &combo);
      }

      //collision avec les briques
      std::vector<brick *>::iterator bri = bricks.begin();
      while (bri != bricks.end())
      {
        if ((*bri)->collision((*b), &future))
        {
          combo++;
          bri = bricks.end();
          bri--;
        }
        bri++;
      }

      future.x += (future.speedx / max_speed_dir);
      future.y += (future.speedy / max_speed_dir);
    }

    //changement de vitesse et de position de la balle
    (*b)->modify_current(future);
  }
}

int terrain::add_point()
{
  int a = pts_per_frame * combo;
  pts_per_frame = 0;
  return a;
}

int terrain::add_life()
{
  int a = b_life_per_frame;
  b_life_per_frame = 0;
  return a;
}

