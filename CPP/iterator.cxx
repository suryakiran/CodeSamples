#include "triplet.hxx"

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
int main (void)
{
	printVector() ;
}
