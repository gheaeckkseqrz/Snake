//
// main.cpp for Snake in /home/wilmot_p/PROJETS/Snake
// 
// Made by WILMOT Pierre
// Login   <wilmot@epitech.net>
// 
// Started on  Thu Apr 26 23:56:55 2012 WILMOT Pierre
// Last update Sat Apr 28 15:53:41 2012 WILMOT Pierre
//

#include	<iostream>

#include	"Map.hpp"

int	main(int ac, char **av)
{
  (void)ac;
  (void)av;

  int	c;

  if (ac >= 2)
    c = atoi(av[1]);
  else
    c = 120;

  Map	m(c);

  int	i(1);
  int	j(0);
  while (1)
    {
      j = 0;
      while (m.hasLivingSnakes() && m.userContinue() && j < 5000)
	{
	  std::cout << "============== Tour " << j << " ================" << std::endl;
	  m.play();
	  j++;
	}
      m.order();
      m.log(i);
      m.mute();
      i++;
    }

  return (0);
}