//
// Map.cpp for Snake in /home/wilmot_p/PROJETS/Snake
// 
// Made by WILMOT Pierre
// Login   <wilmot@epitech.net>
// 
// Started on  Thu Apr 26 22:58:06 2012 WILMOT Pierre
// Last update Sat Apr 28 15:59:46 2012 WILMOT Pierre
//

#include	<algorithm>
#include	<iostream>
#include	<fstream>
#include	<sstream>

#include	"Map.hpp"

Map::Map(int nb_snake)
  :m_continue(true), m_size(nb_snake)
{
  for (int i(0) ; i < nb_snake ; ++i)
    {
      m_snakes.push_back(Snake(*this));
    }
  display();
}

Map::~Map()
{
}

Map::e_caseType		Map::getCase(int x, int y) const
{
  if (x <= 0 || y <= 0 || x >= MAP_X - 1 || y >= MAP_Y - 1)
    return (WALL);
  for (unsigned int i(0) ; i < m_snakes.size() ; ++i)
    {
      if (m_snakes[i].containCdn(Cdn<int>(x, y)))
	return (SNAKE);
    }
  if (std::find(m_food.begin(), m_food.end(), Cdn<int>(x, y)) != m_food.end())
    return (FOOD);
  return(EMPTY);
}

void			Map::display()
{
  sf::Color	c[5] = {sf::Color::Red, sf::Color::Blue, sf::Color::Green,
			sf::Color::Yellow, sf::Color::Cyan};

  m_win->clear();

  for (int i(0) ; i < MAP_X ; ++i)
    {
      for (int j(0) ; j < MAP_X ; ++j)
	{
	  if (i == 0 || j == 0 || i == MAP_X - 1 || j == MAP_Y - 1)
	    drawBloc(Cdn<int>(i, j), sf::Color(127, 127, 127));
	}
    }

  for (unsigned int i(0) ; i < m_food.size() ; ++i)
    {
      drawBloc(m_food[i], c[5]);
    }

  for (unsigned int i(0) ; i < m_snakes.size() ; ++i)
    {
      if (m_snakes[i].getAlive())
	{
	  for (unsigned int j(0) ; j < m_snakes[i].size() ; ++j)
	    drawBloc(m_snakes[i][j], c[i % 4]);
	}
    }
  m_win->display();
}

void				Map::play()
{
  for (unsigned int i(0) ; i < m_snakes.size() ; ++i)
    {
      if (m_snakes[i].getAlive())
	{
	  if (!m_snakes[i].canMove(*this))
	    {
	      m_snakes[i].setAlive(false);
	      std::cout << "Snake sized " << m_snakes[i].size() << " dies =(" << std::endl;
	    }
	  else
	    {
	      m_snakes[i].move(*this);
	      spawnFood();
	      display();
	    }
	}
    }
}

void				Map::spawnFood()
{
  int	x;
  int	y;

  while (m_food.size() < (unsigned int)100)
    {
      do
	{
	  x = rand() % MAP_X;
	  y = rand() % MAP_Y;
	}
      while (getCase(x, y) != Map::EMPTY);
      m_food.push_back(Cdn<int>(x, y));
    }
}

void				Map::deleteFood(int x, int y)
{
  m_food.erase(std::find(m_food.begin(), m_food.end(), Cdn<int>(x, y)));
}

bool				Map::hasLivingSnakes() const
{
  for (unsigned int i(0) ; i < m_snakes.size() ; ++i)
    {
      if (m_snakes[i].getAlive())
	return (true);
    }
  return (false);
}

bool				Map::userContinue() const
{
  return (m_continue);
}

void				Map::log(int i)
{
  std::stringstream	ss;
  ss << "./Logs/" << i << ".txt";
  std::ofstream	logfile(ss.str().c_str());

  logfile << "Vague " << i << std::endl << std::endl;

  for (unsigned int i(0) ; i < m_snakes.size() ; ++i)
    {
      logfile << m_snakes[i].size() << "  " << m_snakes[i] << std::endl;
    }
}

void				Map::mute()
{
  int	k(20);

  while (m_snakes.size() != 20)
    {
      m_snakes.pop_back();
    }
  for (int j(0) ; j <= k ; ++j)
    {
      for (int l(j+1) ; l <= k ; ++l)
        {
	  m_snakes.push_back(Snake(*this, m_snakes[j], m_snakes[l]));
        }
    }
  for (unsigned int i(0) ; i < m_snakes.size() ; ++i)
    {
      m_snakes[i].setAlive(true);
    }
  refill();
}

unsigned int			Map::return_env(Cdn<int> &a) const
{
  unsigned int	result(0);

  if (FoodUp(a))
    result |= 1;
  if (FoodDown(a))
    result |= 2;
  if (FoodLeft(a))
    result |= 4;
  if (FoodRight(a))
    result |= 8;

  if (FoodUpRight(a))
    result |= 16;
  if (FoodUpLeft(a))
    result |= 32;
  if (FoodDownRight(a))
    result |= 64;
  if (FoodDownLeft(a))
    result |= 128;

  return (result);
}

void				Map::order()
{
  std::sort(m_snakes.begin(), m_snakes.end());
  std::reverse(m_snakes.begin(), m_snakes.end());
}

bool				Map::FoodUp(Cdn<int> &a) const
{
  return (FoodIn(a.getX(), a.getX(), 0, a.getY()));
}
bool				Map::FoodDown(Cdn<int> &a) const
{
  return (FoodIn(a.getX(), a.getX(), a.getY(), MAP_Y -1));
}
bool				Map::FoodRight(Cdn<int> &a) const
{
  return (FoodIn(a.getX(), MAP_X - 1, a.getY(), a.getY()));
}
bool				Map::FoodLeft(Cdn<int> &a) const
{
  return (FoodIn(0, a.getX(), a.getY(), a.getY()));
}
bool				Map::FoodUpRight(Cdn<int> &a) const
{
  return (FoodIn(a.getX(), MAP_X -1, 0, a.getY()));
}
bool				Map::FoodUpLeft(Cdn<int> &a) const
{
  return (FoodIn(0, a.getX(), 0, a.getY()));
}
bool				Map::FoodDownRight(Cdn<int> &a) const
{
  return (FoodIn(a.getX(), MAP_X -1, a.getY(), MAP_Y - 1));
}
bool				Map::FoodDownLeft(Cdn<int> &a) const
{
  return (FoodIn(0, a.getX(), a.getY(), MAP_Y - 1));
}

bool				Map::FoodIn(int x1, int x2, int y1, int y2) const
{
  for (unsigned int i(0) ; i < m_food.size() ; ++i)
    {
      if (m_food[i].getX() >= x1 && m_food[i].getX() <= x2 &&
	  m_food[i].getY() >= y1 && m_food[i].getY() <= y2)
	return (true);
    }
  return (false);
}


void				Map::refill()
{
  while (m_snakes.size() < (unsigned int)m_size)
    {
      m_snakes.push_back(Snake(*this));
    }
}
