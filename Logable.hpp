//
// Logable.hpp for Snake in /home/wilmot_p/PROJETS/Snake
// 
// Made by WILMOT Pierre
// Login   <wilmot@epitech.net>
// 
// Started on  Wed May  2 20:33:44 2012 WILMOT Pierre
// Last update Wed May  2 21:39:04 2012 WILMOT Pierre
//

#ifndef __LOGABLE_HPP__
#define __LOGABLE_HPP__

#include        <mysql/mysql.h>
#include	<fstream>

#include	<iostream>

class Logable
{
 public:
  Logable();
  ~Logable();

 protected:
  bool		mysqlOK;
  MYSQL		mysql;
  std::string	mysql_user;
  std::string	mysql_password;
};

#endif
