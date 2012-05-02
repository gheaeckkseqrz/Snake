//
// Logable.cpp for Snake in /home/wilmot_p/PROJETS/Snake
// 
// Made by WILMOT Pierre
// Login   <wilmot@epitech.net>
// 
// Started on  Wed May  2 20:33:48 2012 WILMOT Pierre
// Last update Wed May  2 21:41:55 2012 WILMOT Pierre
//

#include	<sstream>
#include	<iostream>
#include	"Logable.hpp"

#define		MYSQL_CNF	"mysql.cnf"

Logable::Logable()
{
  std::ifstream	mysqlcnf(MYSQL_CNF);

  if (mysqlcnf)
    {
      mysqlcnf >> mysql_user;
      mysqlcnf >> mysql_password;

      mysql_init(&mysql);
      mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");
      if(mysql_real_connect(&mysql, "localhost", mysql_user.c_str(), mysql_password.c_str(), "SNAKE", 0, NULL, 0))
	mysqlOK = true;
      else
	mysqlOK = false;

    }
}

Logable::~Logable()
{
  if (mysqlOK)
    mysql_close(&mysql);
}

