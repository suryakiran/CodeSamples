#ifndef TRIPLET_HXX
#define TRIPLET_HXX

#include "std.hxx"

template <class T>
struct Triplet
{
	T x, y, z ;
	Triplet (const T& p_x, const T& p_y, const T& p_z)
		: x(p_x), y(p_y), z(p_z) { }
} ;

template <class T>
ostream& operator<< (ostream& os, const Triplet<T>& p_t)
{
	os << '(' << p_t.x << ',' << p_t.y << ',' << p_t.z << ')' ;
	return os ;
}
#endif
