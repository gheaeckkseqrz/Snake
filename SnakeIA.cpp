//
// SnakeIA.cpp for Snake in /home/wilmot_p/PROJETS/Snake
// 
// Made by WILMOT Pierre
// Login   <wilmot@epitech.net>
// 
// Started on  Fri Apr 27 13:17:08 2012 WILMOT Pierre
// Last update Sat Apr 28 16:12:47 2012 WILMOT Pierre
//

#include	<iostream>

#include	"SnakeIA.hpp"
#include	"Map.hpp"

SnakeIA::SnakeIA()
{
  char	d[] = "UDRL";

  while (m_gene.size() != 256)
    {
      m_gene.push_back(d[rand() % 4]);
    }
}

SnakeIA::SnakeIA(Snake const &a, Snake const &b)
{
  std::string	c(a.getGene());
  std::string	d(b.getGene());


  while (m_gene.size() != 256)
    {
      if ((m_gene.size()) % 2)
	m_gene.push_back(c[m_gene.size()]);
      else
	m_gene.push_back(d[m_gene.size()]);
    }
}

SnakeIA::~SnakeIA()
{
}

std::string			SnakeIA::getGene() const
{
  return (m_gene);
}

SnakeIA::e_Direction		SnakeIA::getMove(Map const &m, Cdn<int> &head) const
{
  int		env(m.return_env(head));

  if (m_gene[env] == 'U')
    return (UP);
  if (m_gene[env] == 'D')
    return (DOWN);
  if (m_gene[env] == 'R')
    return (RIGHT);
  if (m_gene[env] == 'L')
    return (LEFT);
  return (UP);
}


SnakeIA::e_Direction		SnakeIA::getRandomMove() const
{
  int	i(rand() % 4);

  if (i == 0)
    return (UP);
  if (i == 1)
    return (DOWN);
  if (i == 2)
    return (LEFT);
  if (i == 3)
    return (RIGHT);
  return (UP);
}