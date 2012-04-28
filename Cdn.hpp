//
// Cdn.hpp for Nibbler in /home/wilmot_p/EPITECH/nibbler-2015-molnar_a
// 
// Made by WILMOT Pierre
// Login   <wilmot@epitech.net>
// 
// Started on  Wed Mar 14 15:42:10 2012 WILMOT Pierre
// Last update Fri Apr 27 00:19:08 2012 WILMOT Pierre
//

#ifndef __Cdn_HPP__
#define __Cdn_HPP__

#include <iostream>

template <class T>
class Cdn
{
public:
  Cdn(T x = 0, T y = 0, T z = 0)
    :m_x(x), m_y(y), m_z(z)
  {
  }

  ~Cdn()
  {
  }

  Cdn(const Cdn<int> &o)
  {
    m_x = o.getX();
    m_y = o.getY();
    m_z = o.getZ();
  }

  T	getX() const
  {
    return (m_x);
  }

  T	getY() const
  {
    return (m_y);
  }

  T	getZ() const
  {
    return (m_z);
  }

  void	setX(T x)
  {
    m_x = x;
  }

  void	setY(T y)
  {
    m_y = y;
  }

  void	setZ(T z)
  {
    m_z = z;
  }

  void	incX()
  {
    m_x++;
  }

  void	incY()
  {
    m_y++;
  }

  void	incZ()
  {
    m_z++;
  }

private:
  T		m_x;
  T		m_y;
  T		m_z;
};

std::ostream	&operator<<(std::ostream &os, Cdn<int> const &);

template <class T>
bool		operator==(Cdn<T> const& a, Cdn<T> const& b)
{
  if (a.getX() == b.getX() &&
      a.getY() == b.getY() &&
      a.getZ() == b.getZ())
    return (true);
  return (false);
}


#endif
