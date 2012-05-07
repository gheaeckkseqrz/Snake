//
// Options.cpp for Snake in /home/wilmot_p/PROJETS/Snake
// 
// Made by WILMOT Pierre
// Login   <wilmot@epitech.net>
// 
// Started on  Mon May  7 20:52:03 2012 WILMOT Pierre
// Last update Mon May  7 21:13:05 2012 WILMOT Pierre
//

#include	<stdexcept>
#include	<iostream>
#include	"Options.hpp"

Options::Options()
  :m_fromDB(true), m_infinite(false)
{
}

Options::~Options()
{
}

void		Options::parseOption(int ac, char **av)
{
  std::string	str;

  for (int i(1) ; i < ac ; ++i)
    {
      str = av[i];
      if (str == "--infinite")
	m_infinite = true;
      else if (str == "--fromDB")
	m_fromDB = true;
      else
	{
	  std::cerr << "Argument Invalide : " << str << std::endl;
	  throw std::invalid_argument("Argument Invalide");
	}
    }
}

bool		Options::getFromDB() const
{
  return (m_fromDB);
}

bool		Options::getInfinite() const
{
  return (m_infinite);
}
