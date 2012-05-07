//
// SnakeIA.hpp for Snake in /home/wilmot_p/PROJETS/Snake
// 
// Made by WILMOT Pierre
// Login   <wilmot@epitech.net>
// 
// Started on  Fri Apr 27 13:05:16 2012 WILMOT Pierre
// Last update Mon May  7 09:51:12 2012 WILMOT Pierre
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
  SnakeIA(
	  std::string const &G1,
	  std::string const &G2,
	  std::string const &G3,
	  std::string const &G4,
	  std::string const &G5
	  );
  ~SnakeIA();

  e_Direction			getMove(Map const &m, Cdn<int> &head) const;
  e_Direction			getRandomMove() const;
  std::string			getGene(int i) const;

protected:
  std::string			m_gene[5];
  int				m_score;
  int				m_eated;
};

#endif
