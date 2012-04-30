//
// Snake.cpp for Snake in /home/wilmot_p/PROJETS/Snake
// 
// Made by WILMOT Pierre
// Login   <wilmot@epitech.net>
// 
// Started on  Thu Apr 26 21:05:14 2012 WILMOT Pierre
// Last update Mon Apr 30 21:16:58 2012 WILMOT Pierre
//

#include	<algorithm>
#include	<iostream>
#include	"Map.hpp"
#include	"Snake.hpp"

#define	START_SIZE	4

Snake::Snake(Map const &m)
  :toGrow(0), m_alive(true)
{
  placeHead(m);
}

Snake::Snake(Map const &m, Snake const &a, Snake const &b)
  :SnakeIA(a, b), toGrow(0), m_alive(true)
{
  placeHead(m);
}

// Snake::Snake(Map const &m, std::string const &g)
//   :SnakeIA(g), toGrow(0), m_alive(true)
// {
//   placeHead(m);
// }

Snake::~Snake()
{
  std::cout << "Snake dying at size " << size() << std::endl;
}

void				Snake::placeHead(Map const &m)
{
  int	x;
  int	y;

  while (m_snake.size() != START_SIZE)
    {
      if (m_snake.empty())
	{
	  do
	    {
	      x = rand() % MAP_X;
	      y = rand() % MAP_Y;
	      std::cout << "Placing head on " << x << "/" << y << " : " << m.getCase(x, y) << std::endl;
	    }
	  while (m.getCase(x, y) != Map::EMPTY);
	  m_snake.push_back(Cdn<int>(x, y));
	}
      if (!appendSnake(START_SIZE - 1, m))
	m_snake.clear();
    }
}

bool				Snake::getAlive() const
{
  return (m_alive);
}

void				Snake::setAlive(bool a)
{
  m_alive = a;
}


bool				Snake::appendSnake(int n, Map const &m)
{
  Cdn<int>			last;
  std::vector<Cdn<int> >	p;

  if (n == 0)
    return true;

  p.push_back(Cdn<int>(1, 0));
  p.push_back(Cdn<int>(-1, 0));
  p.push_back(Cdn<int>(0, 1));
  p.push_back(Cdn<int>(0, -1));
  last = m_snake.back();

  for (int i(0) ; i < 4 ; ++i)
    {
      m_snake.push_back(Cdn<int>(last.getX() + p[i].getX(), last.getY() + p[i].getY()));
      if (appendSnake(n - 1, m) == true)
	return (true);
      else
	m_snake.pop_back();
    }
  return (false);
}

bool				Snake::containCdn(Cdn<int> const &c) const
{
  if (std::find(m_snake.begin(), m_snake.end(), c) != m_snake.end())
    return (true);
  return (false);
}

unsigned int			Snake::size() const
{
  return (m_snake.size());
}

void				Snake::display(std::ostream &s) const
{
  for (unsigned int i(0) ; i < m_snake.size() ; ++i)
    {
      s << "[" << m_snake[i].getX() << "/" << m_snake[i].getY() << "]";
    }
  s << "-  [" << m_gene << "]";
}

void				Snake::move(Map &m)
{
  Map::e_caseType	c;
  SnakeIA::e_Direction	d;
  Cdn<int>		head(m_snake.back());
  bool			moved(false);

  d = getMove(m, head);
  while (moved == false)
    {
      if (d == UP)
	{
	  if ((c = m.getCase(head.getX(), head.getY() - 1)) == Map::EMPTY ||
	      c == Map::FOOD)
	    {
	      if (c == Map::FOOD)
		m.deleteFood(head.getX(), head.getY() - 1);
	      m_snake.push_back(Cdn<int>(head.getX(), head.getY() - 1));
	      moved = true;
	    }
	}
      if (d == DOWN)
	{
	  if ((c = m.getCase(head.getX(), head.getY() + 1)) == Map::EMPTY ||
	      c == Map::FOOD)
	    {
	      if (c == Map::FOOD)
		m.deleteFood(head.getX(), head.getY() + 1);
	      m_snake.push_back(Cdn<int>(head.getX(), head.getY() + 1));
	      moved = true;
	    }
	}
      if (d == LEFT)
	{
	  if ((c = m.getCase(head.getX() - 1, head.getY())) == Map::EMPTY ||
	      c == Map::FOOD)
	    {
	      if (c == Map::FOOD)
		m.deleteFood(head.getX() - 1, head.getY());
	      m_snake.push_back(Cdn<int>(head.getX() - 1, head.getY()));
	      moved = true;
	    }
	}
      if (d == RIGHT)
	{
	  if ((c = m.getCase(head.getX() + 1, head.getY())) == Map::EMPTY ||
	      c == Map::FOOD)
	    {
	      if (c == Map::FOOD)
		{
		  m.deleteFood(head.getX() + 1, head.getY());
		  m_eated++;
		}
		m_snake.push_back(Cdn<int>(head.getX() + 1, head.getY()));
		moved = true;
	    }
	}
      d = getRandomMove();
    }
  if (c == Map::FOOD)
    toGrow++;
  if (toGrow == 0)
    m_snake.erase(m_snake.begin());
  else
    {
      std::cout << "I'm Growing, my size is " << m_snake.size() << std::endl;
      toGrow--;
    }
}

bool				Snake::canMove(Map const &m) const
{
  Cdn<int>		head(m_snake.back());

  if (m.getCase(head.getX(), head.getY() - 1) == Map::EMPTY)
    return (true);
  if (m.getCase(head.getX(), head.getY() + 1) == Map::EMPTY)
    return (true);
  if (m.getCase(head.getX() + 1, head.getY()) == Map::EMPTY)
    return (true);
  if (m.getCase(head.getX() - 1, head.getY()) == Map::EMPTY)
    return (true);
  return (false);
}

void				Snake::rePlace(Map const &m)
{
  m_snake.clear();
  placeHead(m);
}

Cdn<int>			Snake::operator[](unsigned int i)
{
  return (m_snake[i]);
}

std::ostream			&operator<<(std::ostream &s, Snake const &a)
{
  a.display(s);
  return (s);
}

bool				operator<(Snake const &a, Snake const &b)
{
  return (a.size() < b.size());
}

