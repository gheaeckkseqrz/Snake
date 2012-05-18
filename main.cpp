//
// main.cpp for Snake in /home/wilmot_p/PROJETS/Snake
// 
// Made by WILMOT Pierre
// Login   <wilmot@epitech.net>
// 
// Started on  Thu Apr 26 23:56:55 2012 WILMOT Pierre
// Last update Sat May 19 00:37:22 2012 WILMOT Pierre
//

#include	<iostream>

#include	"Options.hpp"
#include	"Map.hpp"

int	main(int ac, char **av)
{
  (void)ac;
  (void)av;

  Options	o;
  int	c(250);
  int	best(0);
  int	best2(0);

  o.parseOption(ac, av);

  if (o.getInfinite())
    c = 5;

  Map	m(c, o.getFromDB());

  if (o.getInfinite())
    {
      while (m.hasLivingSnakes())
	m.play();
    }
  else
    {
      int	i(1);
      int	j(0);
      int	nb_tour(600);
      while (1)
	{
	  m.setTittle(i);
	  j = 0;
	  while (m.hasLivingSnakes() && m.userContinue() && j < nb_tour)
	    {
	      std::cout << "============== Tour [" << i << "] | " << j << "/" << nb_tour << " (" << best2 << ")(" << best << ")================" << std::endl;
	      m.play();
	      j++;
	    }
	  m.order();
	  best2 = m.fileLog(i);
	  m.mysqlLog(i);
	  if (best2 > best)
	    best = best2;
	  nb_tour = best * 150;
	  m.mute();
	  i++;
	}
    }
  return (0);
}
