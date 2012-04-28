//
// Display.hpp for Snake in /home/wilmot_p/PROJETS/Snake
// 
// Made by WILMOT Pierre
// Login   <wilmot@epitech.net>
// 
// Started on  Fri Apr 27 00:48:22 2012 WILMOT Pierre
// Last update Fri Apr 27 08:40:20 2012 WILMOT Pierre
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

protected:
  sf::RenderWindow      *m_win;

};

#endif
