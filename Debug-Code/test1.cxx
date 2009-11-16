#include <iostream>
#include <string>
#include <vector>
#include <set>

#include <boost/foreach.hpp>
using namespace std ;

int main (void)
{
	cout << "------ BEGIN ------------" << endl ;
	vector<string> vs ;
	set<string> ss ;

	vs.push_back ("Surya") ;
	vs.push_back ("Kiran") ;

	ss.insert ("Surya") ;
	ss.insert ("Kiran") ;

	BOOST_FOREACH (const string& s, vs)
		cout << s << endl ;

	cout << "-------------------------" << endl ;
	BOOST_FOREACH (const string& s, ss)
		cout << s << endl ;
	cout << "------ END --------------" << endl ;

	return 0 ;
}
