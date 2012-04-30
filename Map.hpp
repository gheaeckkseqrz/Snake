//
// Map.hpp for Snake in /home/wilmot_p/PROJETS/Snake
// 
// Made by WILMOT Pierre
// Login   <wilmot@epitech.net>
// 
// Started on  Thu Apr 26 20:49:18 2012 WILMOT Pierre
// Last update Mon Apr 30 21:02:01 2012 WILMOT Pierre
//

#ifndef __MAP_HPP__
#define __MAP_HPP__

#include	<vector>
#include	<iostream>

#include	"Display.hpp"
#include	"Cdn.hpp"
#include	"Snake.hpp"

#define	MAP_X	256
#define	MAP_Y	256

class Map : public Display
{
public:

enum e_caseType
  {
    EMPTY,
    SNAKE,
    FOOD,
    WALL
  };

public:
  Map(int nb_snake);
  ~Map();

  Map::e_caseType		getCase(int x, int y) const;
  void				display();
  void				play();
  void				spawnFood();
  void				deleteFood(int x, int y);
  bool				hasLivingSnakes() const;
  unsigned int			return_env1(Cdn<int> &a) const;
  unsigned int			return_env2(Cdn<int> &a) const;
  unsigned int			return_env3(Cdn<int> &a) const;
  unsigned int			return_env4(Cdn<int> &a) const;
  void				order();
  bool				userContinue() const;
  unsigned int			log(int i);
  void				mute();
  void				refill();
  // void				pushSnake(std::string g);

private:
  bool				FoodUp(Cdn<int> &a) const;
  bool				FoodDown(Cdn<int> &a) const;
  bool				FoodRight(Cdn<int> &a) const;
  bool				FoodLeft(Cdn<int> &a) const;

  bool				FoodUpRight(Cdn<int> &a) const;
  bool				FoodUpLeft(Cdn<int> &a) const;
  bool				FoodDownRight(Cdn<int> &a) const;
  bool				FoodDownLeft(Cdn<int> &a) const;

  bool				FoodIn(int x1, int x2, int y1, int y2) const;
  bool				Caseis(Cdn<int> &a, int i, e_caseType ct) const;

private:
  std::vector<Cdn<int> >	m_food;
  std::vector<Snake>		m_snakes;
  unsigned int			m_tour;
  bool				m_continue;
  int				m_size;
};

#endif
