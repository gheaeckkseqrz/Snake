//
// Options.hpp for Snake in /home/wilmot_p/PROJETS/Snake
// 
// Made by WILMOT Pierre
// Login   <wilmot@epitech.net>
// 
// Started on  Mon May  7 20:51:59 2012 WILMOT Pierre
// Last update Mon May  7 20:54:08 2012 WILMOT Pierre
//

#ifndef __OPTIONS_HPP__
#define __OPTIONS_HPP__

#include	<iostream>

class Options
{
public:
  Options();
  ~Options();

  void		parseOption(int ac, char **av);
  bool		getFromDB() const;
  bool		getInfinite() const;

private:
  bool		m_fromDB;
  bool		m_infinite;
};

#endif
