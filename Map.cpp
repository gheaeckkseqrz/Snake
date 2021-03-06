//
// Map.cpp for Snake in /home/wilmot_p/PROJETS/Snake
// 
// Made by WILMOT Pierre
// Login   <wilmot@epitech.net>
// 
// Started on  Thu Apr 26 22:58:06 2012 WILMOT Pierre
// Last update Tue May  8 10:11:23 2012 WILMOT Pierre
//

#include	<algorithm>
#include	<iostream>
#include	<fstream>
#include	<sstream>
#include	<cmath>
#include	<unistd.h>
#include	<ctime>

#include	"Map.hpp"

Map::Map(int nb_snake, bool fromDB)
  :m_continue(true), m_size(nb_snake)
{
  char	hostname[512];

  if (fromDB)
    {
      MYSQL_RES		*result(NULL);
      MYSQL_ROW		row(NULL);

      mysql_query(&mysql, "SELECT  *, MAX(Score) FROM Genes GROUP BY gameid");
      result = mysql_use_result(&mysql);
      while ((row = mysql_fetch_row(result)))
        {
	  m_snakes.push_back(Snake(*this, row[3], row[4], row[5], row[6], row[7]));
        }
    }
  while ((int)m_snakes.size() < nb_snake)
    {
	m_snakes.push_back(Snake(*this));
    }
  display();
  gethostname(hostname, 512);

  time_t		t = time(0);
  struct tm *		now = localtime(&t);
  std::stringstream	ss;

  ss << hostname << "_" << (now->tm_year + 1900) << "-"
     << (now->tm_mon + 1) << "-"
     <<  now->tm_mday << "_"
     << getpid();

  m_gameId = ss.str();
  std::cout << m_gameId << std::endl;
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
	return (WALL);
    }
  if (std::find(m_food.begin(), m_food.end(), Cdn<int>(x, y)) != m_food.end())
    return (FOOD);
  return(EMPTY);
}

void			Map::display()
{
  sf::Color	orange(255, 128, 0);
  sf::Color	c[7] = {sf::Color::Blue,
			sf::Color::Green,
			sf::Color::Yellow,
			sf::Color::Magenta,
			sf::Color::Cyan,
			orange,
			sf::Color::Red      };

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
      drawBloc(m_food[i], c[6]);
    }

  for (unsigned int i(0) ; i < m_snakes.size() ; ++i)
    {
      for (unsigned int j(0) ; j < m_snakes[i].size() ; ++j)
	{
	  if (m_snakes[i].getAlive())
	    drawBloc(m_snakes[i][j], c[i % 6]);
	  else
	    drawBloc(m_snakes[i][j], sf::Color(127, 127, 127));
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

void				Map::mute()
{
  int	k(40); // Keep
  int	m(20); // Mute
  if ((int)m_snakes.size() <= 40)
    {
      k = 4;
      m = 2;
    }

  while ((int)m_snakes.size() > k)
    {
      m_snakes.pop_back();
    }
  for (int j(0) ; j <= k ; ++j)
    {
      m_snakes[j].rePlace(*this);
      if (j < m)
	{
	  for (int l(j+1) ; l <= m ; ++l)
	    {
	      m_snakes.push_back(Snake(*this, m_snakes[j], m_snakes[l]));
	    }
	}
    }
  for (unsigned int i(0) ; i < m_snakes.size() ; ++i)
    {
      m_snakes[i].setAlive(true);
    }
  refill();
}

// ================ RETURN ENV FUNC

unsigned int			Map::return_env1(Cdn<int> &a) const
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

unsigned int			Map::return_env2(Cdn<int> &a) const
{
  unsigned int	result(0);

  if (getCase(a.getX(), a.getY() - 1) == FOOD)
    result |= 1;
  if (getCase(a.getX() + 1, a.getY() - 1) == FOOD)
    result |= 2;
  if (getCase(a.getX() + 1, a.getY()) == FOOD)
    result |= 4;
  if (getCase(a.getX() + 1, a.getY() + 1) == FOOD)
    result |= 8;
  if (getCase(a.getX(), a.getY() + 1) == FOOD)
    result |= 16;
  if (getCase(a.getX() - 1, a.getY() + 1) == FOOD)
    result |= 32;
  if (getCase(a.getX() - 1, a.getY()) == FOOD)
    result |= 64;
  if (getCase(a.getX() - 1, a.getY() - 1) == FOOD)
    result |= 128;
  return (result);
}

unsigned int			Map::return_env3(Cdn<int> &a) const
{
  unsigned int	result(0);

  if (getCase(a.getX(), a.getY() - 1) == WALL)
    result |= 1;
  if (getCase(a.getX() + 1, a.getY() - 1) == WALL)
    result |= 2;
  if (getCase(a.getX() + 1, a.getY()) == WALL)
    result |= 4;
  if (getCase(a.getX() + 1, a.getY() + 1) == WALL)
    result |= 8;
  if (getCase(a.getX(), a.getY() + 1) == WALL)
    result |= 16;
  if (getCase(a.getX() - 1, a.getY() + 1) == WALL)
    result |= 32;
  if (getCase(a.getX() - 1, a.getY()) == WALL)
    result |= 64;
  if (getCase(a.getX() - 1, a.getY() - 1) == WALL)
    result |= 128;
  return (result);
}

unsigned int			Map::return_env4(Cdn<int> &a) const
{
  unsigned int	result(0);

  if (FoodIn(a.getX(), a.getY() - 4, a.getX(), a.getY()))
    result |= 1;
  if (FoodIn(a.getX(), a.getY(), a.getX(), a.getY() + 4))
    result |= 2;
  if (FoodIn(a.getX() - 4, a.getY(), a.getX(), a.getY()))
    result |= 4;
  if (FoodIn(a.getX(), a.getY(), a.getX() + 4, a.getY()))
    result |= 8;
  if (FoodIn(a.getX(), a.getY() - 4, a.getX() + 4, a.getY()))
    result |= 16;
  if (FoodIn(a.getX() - 4, a.getY() - 4, a.getX(), a.getY() - 4))
    result |= 32;
  if (FoodIn(a.getX() - 4, a.getY(), a.getX(), a.getY() + 4))
    result |= 64;
  if (FoodIn(a.getX(), a.getY(), a.getX() + 4, a.getY() + 4))
    result |= 128;
  return (result);
}

void				Map::order()
{
  std::sort(m_snakes.begin(), m_snakes.end());
  std::reverse(m_snakes.begin(), m_snakes.end());
}


void				Map::refill()
{
  while (m_snakes.size() < (unsigned int)m_size)
    {
      m_snakes.push_back(Snake(*this));
    }
}

bool				Map::Caseis(Cdn<int> &a, int i, e_caseType ct) const
{
  static int			init(false);
  static std::vector<Cdn<int> >	c;

  if (!init)
    {
      c.push_back(Cdn<int>(0, -1));
      c.push_back(Cdn<int>(1, -1));
      c.push_back(Cdn<int>(1, 0));
      c.push_back(Cdn<int>(1, 1));
      c.push_back(Cdn<int>(0, 1));
      c.push_back(Cdn<int>(-1, 1));
      c.push_back(Cdn<int>(-1, 0));
      c.push_back(Cdn<int>(-1, -1));
      init = true;
    }
  return (getCase(a.getX() + c[i].getX(), a.getY() + c[i].getY()) == ct);
}

// ========================== PRIVATE FUNC

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

// ===================== LOG FUNC

unsigned int	Map::fileLog(int i)
{
  unsigned int			best(0);
  std::stringstream		ss;

  ss << "./Logs/" << i << ".txt";
  std::ofstream			logfile(ss.str().c_str());

  logfile << "Vague " << i << std::endl << std::endl;

  best = m_snakes[0].size();
  for (unsigned int i(0) ; i < m_snakes.size() ; ++i)
    {
      if (m_snakes[i].size() > best)
	best = m_snakes[i].size();
      logfile << "Size : " << m_snakes[i].size() << std::endl;
      for (int j(0) ; j < 5 ; ++j)
	{
	  logfile << m_snakes[i].getGene(j) << std::endl;
	}
    }
  logfile.close();
  return (best);
}

unsigned int	Map::mysqlLog(int t)
{
  unsigned int			best(0);
  std::stringstream		ss;

  if (mysqlOK)
    {
      best = m_snakes[0].size();
      for (unsigned int i(0) ; i < m_snakes.size() ; ++i)
	{
	  if (m_snakes[0].size() > best)
	    best = m_snakes[0].size();
	  if (m_snakes[0].size() > 4)
	    {
	      ss << "INSERT INTO Genes(id, gameid, Phase, G1, G2, G3, G4, G5, Score) VALUES('', ";
	      ss << "'" << m_gameId << "'" << ", ";
	      ss << t << ", ";
	      for (int j(0) ; j < 5 ; ++j)
		ss << "'" << m_snakes[i].getGene(j) << "', ";
	      ss << m_snakes[i].size();
	      ss << ");";
	      mysql_query(&mysql, ss.str().c_str());
	      ss.str("");
	    }
	}
    }
  return (best);
}


// void				Map::pushSnake(std::string g)
// {
//   m_snakes.push_back(Snake(*this, g));
// }
