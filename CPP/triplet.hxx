#ifndef TRIPLET_HXX
#define TRIPLET_HXX 1

#include <std.hxx>

namespace skg 
{
	template <class T>
		struct Triplet
		{
			private:
			T x, y, z ;

			public:
			Triplet (const T& p_x, const T& p_y, const T& p_z)
				: x(p_x), y(p_y), z(p_z) { }

			void get (T& p_x, T& p_y, T& p_z) const
			{ p_x = x ; p_y = y; p_z = z ; }
		} ;
}

template <class T>
ostream& operator<< (ostream& os, const skg::Triplet<T>& p_t)
{
	T x, y, z ;
	p_t.get(x, y, z) ;
	os << '(' << x << ',' << y << ',' << z << ')' ;
	return os ;
}
#endif
