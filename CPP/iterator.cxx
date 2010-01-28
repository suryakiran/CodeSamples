#include "triplet.hxx"

namespace {
	void printVector()
	{
		typedef Triplet<int> IntTriplet ;

		vector< IntTriplet > vti ;
		vti.push_back (IntTriplet (1, 2, 3)) ;
		vti.push_back (IntTriplet (5, 5, 66)) ;

		copy (vti.begin(), vti.end(), ostream_iterator<IntTriplet> (cout, "\n")) ;
	}
}
int main (void)
{
	printVector() ;
}
