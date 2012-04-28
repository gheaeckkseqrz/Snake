//
// SnakeIA.hpp for Snake in /home/wilmot_p/PROJETS/Snake
// 
// Made by WILMOT Pierre
// Login   <wilmot@epitech.net>
// 
// Started on  Fri Apr 27 13:05:16 2012 WILMOT Pierre
// Last update Sat Apr 28 15:02:58 2012 WILMOT Pierre
//

#ifndef __SNAKEIA_HPP__
#define __SNAKEIA_HPP__

#include	<iostream>
#include	<cstdlib>

class	Snake;
#include	"Cdn.hpp"

class	Map;

class SnakeIA
{
public:

  enum e_Direction
    {
      UP,
      DOWN,
      RIGHT,
      LEFT
    };

public:
  SnakeIA();
  SnakeIA(Snake const &a, Snake const &b);
  ~SnakeIA();

  e_Direction			getMove(Map const &m, Cdn<int> &head) const;
  e_Direction			getRandomMove() const;
  std::string			getGene() const;

protected:
  std::string			m_gene;
  int				m_score;
  int				m_eated;
};

#endif
