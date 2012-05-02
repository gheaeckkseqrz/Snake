//
// main.cpp for Snake in /home/wilmot_p/PROJETS/Snake
// 
// Made by WILMOT Pierre
// Login   <wilmot@epitech.net>
// 
// Started on  Thu Apr 26 23:56:55 2012 WILMOT Pierre
// Last update Wed May  2 21:34:43 2012 WILMOT Pierre
//

#include	<iostream>

#include	"Map.hpp"

int	main(int ac, char **av)
{
  (void)ac;
  (void)av;

  int	c;
  int	best(0);
  int	best2(0);

  if (ac >= 2)
    c = atoi(av[1]);
  else
    c = 250;

  Map	m(c);

  int	i(1);
  int	j(0);
  int	nb_tour(100);
  while (1)
    {
      m.setTittle(i);
      j = 0;
      while (m.hasLivingSnakes() && m.userContinue() && j < nb_tour)
  	{
  	  std::cout << "============== Tour [" << i << "] | " << j << "/" << nb_tour << " (" << best << ")================" << std::endl;
  	  m.play();
  	  j++;
  	}
      m.order();
      best2 = m.fileLog(i);
      m.mysqlLog(i);
      if (best2 > best)
  	best = best2;
      nb_tour = best * 20;
      m.mute();
      i++;
    }

  return (0);
}
