//
// main.cpp for Snake in /home/wilmot_p/PROJETS/Snake
// 
// Made by WILMOT Pierre
// Login   <wilmot@epitech.net>
// 
// Started on  Thu Apr 26 23:56:55 2012 WILMOT Pierre
// Last update Sun Apr 29 19:30:27 2012 WILMOT Pierre
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

  m.pushSnake("UDLURUDLLRLDDDLUDUUULRRULDDUDRLURLLDDRLDLUDURURDLLURULDLRRURRLDURUDRDRLLLDRUDDDLRRUDLLRDUUDRRRLDLDLDDLRRUUDLULRDULDRULDLLRLRDDRLRUDDUDLULDRLUDRDLLURLRLRUUURUDRLLRRULUUULURRLULRLLDRRLDRLRUULRRUDLLLLDLDRLDUDRLRULLLURDDRRLLLUDURLDLLRLLDLRUDDRLDUULLUDRRRLRRUDL");
  m.pushSnake("UDLDRDDDLLLLULRRDLDUDUDRLDDLULUULDDRDRDLLLLDLDUDRDRRULDURDDDLRRDURLRLULDDUDDURRRLLRDUDRLRDDUURLLUDLDRLDUUDDDULULLDRDRRLDUDDUULDDRDLRRDULLUURUDRRRRUUULUULLDDDUULLUUDULUDRDRLUDRUUULLDLDUDUDDDLRDDDDRLLDURRLLUURRUURLDRLRRDRLDLLDLLDURRLRRLUUUDULLULDDLUDRRRDRURD");

  int	i(1);
  int	j(0);
  while (1)
    {
      m.setTittle(i);
      j = 0;
      while (m.hasLivingSnakes() && m.userContinue() && j < 5000)
	{
	  std::cout << "============== Tour " << i << "/" << j << " (" << best << ")================" << std::endl;
	  m.play();
	  j++;
	}
      m.order();
      best2 = m.log(i);
      if (best2 > best)
	best = best2;
      m.mute();
      i++;
    }

  return (0);
}
