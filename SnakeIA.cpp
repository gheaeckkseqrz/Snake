//
// SnakeIA.cpp for Snake in /home/wilmot_p/PROJETS/Snake
// 
// Made by WILMOT Pierre
// Login   <wilmot@epitech.net>
// 
// Started on  Fri Apr 27 13:17:08 2012 WILMOT Pierre
// Last update Mon Apr 30 22:00:10 2012 WILMOT Pierre
//

#include	<iostream>

#include	"SnakeIA.hpp"
#include	"Map.hpp"

#define		GENE_SIZE (256)

SnakeIA::SnakeIA()
{
  char	d[] = "UDRL";

  for (int i(0); i < 5 ; ++i)
    {
      while (m_gene[i].size() != GENE_SIZE)
	{
	  m_gene[i].push_back(d[rand() % 4]);
	}
    }
}

SnakeIA::SnakeIA(Snake const &a, Snake const &b)
{
  std::string	c;
  std::string	d;

  for (int i(0); i < 5 ; ++i)
    {
      c = a.getGene(i);
      d = b.getGene(i);
      while (m_gene[i].size() != 256)
	{
	  if (rand() % 2)
	    {
	      if ((m_gene[i].size()) % 2)
		m_gene[i].push_back(c[m_gene[i].size()]);
	      else
		m_gene[i].push_back(d[m_gene[i].size()]);
	    }
	}
    }
}

SnakeIA::~SnakeIA()
{
}

std::string			SnakeIA::getGene(int i) const
{
  return (m_gene[i]);
}

SnakeIA::e_Direction		SnakeIA::getMove(Map const &m, Cdn<int> &head) const
{
  unsigned int		result(0);

  unsigned int		env[4];

  env[0] = (m.return_env1(head));
  env[1] = (m.return_env2(head));
  env[2] = (m.return_env3(head));
  env[3] = (m.return_env4(head));

  int	b(1);
  for (int i(0) ; i < 4 ; ++i)
    {
      if (m_gene[i][env[i]] == 'U')
	result += 0 * b;
      if (m_gene[i][env[i]] == 'D')
	result += 1 * b;
      if (m_gene[i][env[i]] == 'R')
	result += 2 * b;
      if (m_gene[i][env[i]] == 'L')
	result += 3 * b;
      b *= 4;
    }

  if (m_gene[4][result] == 'U')
    return (UP);
  if (m_gene[4][result] == 'D')
    return (DOWN);
  if (m_gene[4][result] == 'R')
    return (RIGHT);
  if (m_gene[4][result] == 'L')
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
