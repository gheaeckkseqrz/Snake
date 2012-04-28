//
// Display.hpp for Snake in /home/wilmot_p/PROJETS/Snake
// 
// Made by WILMOT Pierre
// Login   <wilmot@epitech.net>
// 
// Started on  Fri Apr 27 00:48:22 2012 WILMOT Pierre
// Last update Sat Apr 28 22:04:17 2012 WILMOT Pierre
//

#ifndef __DISPLAY_HPP__
#define __DISPLAY_HPP__

#include	<iostream>

#include        <SFML/System.hpp>
#include        <SFML/Graphics.hpp>

#include	"Cdn.hpp"

class Display
{
public:
  Display();
  ~Display() {};

  void		drawBloc(Cdn<int> const&c, sf::Color const &a);
  void		setTittle(int i);

protected:
  sf::RenderWindow      *m_win;

};

#endif
