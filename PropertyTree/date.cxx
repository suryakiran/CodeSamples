#include "std.hxx"

#include <boost/date_time/gregorian/gregorian.hpp>

using namespace boost::gregorian ;

#include "propertytree.hxx"

int main (void)
{
	PropertyTree tree ;

	date d (2008,Dec,18) ;
	tree.put ("Test.String", "Ting") ;
	tree.put ("Test.Boolean", false) ;
	tree.setValue ("Test.Date", d) ;

	tree.printTree() ;

	cout.imbue (locale(cout.getloc(), new date_facet("%y/%m/%B"))) ;
	cout << tree.getValue<date> ("Test.Date") << endl ;
	return 0 ;
}
