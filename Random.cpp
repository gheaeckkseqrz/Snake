//
// Random.cpp for gen in /home/wilmot_p/PROJETS/Algo genetiques
// 
// Made by WILMOT Pierre
// Login   <wilmot@epitech.net>
// 
// Started on  Mon Apr 23 21:57:26 2012 WILMOT Pierre
// Last update Tue Apr 24 14:12:49 2012 WILMOT Pierre
//

#include <iostream>
#include "Random.hpp"

Random::Random()
{
  static bool	init(false);

  if (!init)
    {
      srand(getpid());
      init = true;
    }
}
