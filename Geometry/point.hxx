#ifndef POINT_HXX
#define POINT_HXX 1

#include <std.hxx>
#include <boost/array.hpp>

struct Point2d : public boost::array <float, 2>
{
  Point2d()
  {
    fill (0.0f);
  }

  Point2d (float p_x, float p_y)
  {
    elems[0] = p_x;
    elems[1] = p_y;
  }

  const float& x () const {
    return elems[0];
  }

  const float& y () const {
    return elems[1];
  }

  float& x() {
    return elems[0];
  }

  float& y() {
    return elems[1];
  }

  friend
  ostream& operator<< (ostream& p_os, const Point2d& p)
  {
    p_os << 
      fmt ("(%1%, %2%)") % p.x() % p.y() ;

    return p_os;
  }
};

struct Point3d : public boost::array <float, 3>
{
  Point3d ()
  {
    fill (0.0f);
  }

  Point3d (float p_x, float p_y, float p_z)
  {
    elems[0] = p_x;
    elems[1] = p_y;
    elems[2] = p_z;
  }

  const float& x () const {
    return elems[0];
  }

  const float& y () const {
    return elems[1];
  }

  const float& z () const {
    return elems[2];
  }

  float& x() {
    return elems[0];
  }

  float& y() {
    return elems[1];
  }

  float& z() {
    return elems[2];
  }

  friend
  ostream& operator<< (ostream& p_os, const Point3d& p)
  {
    p_os << 
      fmt ("(%1%, %2%, %3%)") % p.x() % p.y() % p.z() ;

    return p_os;
  }
};

#endif
