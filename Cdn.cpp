//
// Cdn.cpp for Nibbler in /home/wilmot_p/EPITECH/nibbler-2015-molnar_a
// 
// Made by WILMOT Pierre
// Login   <wilmot@epitech.net>
// 
// Started on  Wed Mar 14 15:43:30 2012 WILMOT Pierre
// Last update Fri Apr 27 00:16:58 2012 WILMOT Pierre
//


#include <iostream>
#include "Cdn.hpp"

/*
** Classe templatee, cf Cdn.hpp
*/

std::ostream&	operator<<(std::ostream &os, Cdn<int> const &other)
{
  os<<"Cdn : [X: "<<other.getX()<< ", Y: "<<other.getY()<<"]";
  return (os);
}
