//
// Snake.hpp for Snake in /home/wilmot_p/PROJETS/Snake
// 
// Made by WILMOT Pierre
// Login   <wilmot@epitech.net>
// 
// Started on  Thu Apr 26 20:59:37 2012 WILMOT Pierre
// Last update Mon Apr 30 19:31:53 2012 WILMOT Pierre
//

#ifndef __SNAKE_HPP__
#define __SNAKE_HPP__

#include	<iostream>

class	Map;
#include	"Cdn.hpp"
#include	"Random.hpp"
#include	"SnakeIA.hpp"

class Snake : public Random, public SnakeIA
{
public:
  Snake(Map const &m);
  // Snake(Map const &m, std::string const &g);
  Snake(Map const &m, Snake const &a, Snake const &b);
  ~Snake();

  bool				getAlive() const;
  void				setAlive(bool a);

  void				placeHead(Map const &m);
  bool				containCdn(Cdn<int> const &c) const;
  unsigned int			size() const;
  void				display(std::ostream &s) const;
  void				move(Map &m);
  bool				canMove(Map const &m) const;
  void				rePlace(Map const &m);

  Cdn<int>			operator[](unsigned int i);

private:
  bool				appendSnake(int n, Map const &m);

private:
  std::vector<Cdn<int> >	m_snake;
  int				toGrow;
  bool				m_alive;
};

std::ostream			&operator<<(std::ostream &s, Snake const &a);
bool				operator<(Snake const &a, Snake const &b);

#endif
