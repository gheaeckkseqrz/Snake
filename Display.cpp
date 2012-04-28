//
// Display.cpp for Snake in /home/wilmot_p/PROJETS/Snake
// 
// Made by WILMOT Pierre
// Login   <wilmot@epitech.net>
// 
// Started on  Fri Apr 27 00:48:27 2012 WILMOT Pierre
// Last update Sat Apr 28 17:35:27 2012 WILMOT Pierre
//

#include	<iostream>
#include	"Display.hpp"

Display::Display()
{
  m_win = new  sf::RenderWindow(sf::VideoMode(768, 768), "Snake");
}

void		Display::drawBloc(Cdn<int> const&c, sf::Color const &a)
{
  sf::RectangleShape bloc;

  bloc.setSize(sf::Vector2f(3, 3));
  bloc.setOutlineColor(a);
  bloc.setOutlineThickness(1);
  bloc.setPosition(c.getX()*3, c.getY()*3);
  m_win->draw(bloc);
}
