#include "triplet.hxx"
#include "std.hxx"

#include <boost/iterator/filter_iterator.hpp>

namespace {
	void printVector()
	{
		typedef skg::Triplet<int> IntTriplet ;

		vector< IntTriplet > vti ;
		vti.push_back (IntTriplet (1, 2, 3)) ;
		vti.push_back (IntTriplet (5, 5, 66)) ;

		const IntTriplet& it = vti[0] ;

//		copy (vti.begin(), vti.end(), ostream_iterator<IntTriplet> (cout, "\n")) ;

		cout << it << endl ;
	}
}

struct isEven
{
  bool operator()(int i) const
  {
    return ((i % 2) == 0);
  }
};

int main (void)
{
  stl::IntVector vi;
  vi += 1,2,3,4,5,6,7,8,9,10;
  auto i = boost::make_filter_iterator (isEven(), vi.begin(), vi.end());

  while (i != boost::make_filter_iterator (isEven(), vi.end()))
  {
    cout << *i << endl;
    ++i;
  }
}
