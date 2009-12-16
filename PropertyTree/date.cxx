#include "std.hxx"

#include <boost/date_time/gregorian/gregorian.hpp>

using namespace boost::gregorian ;

#include "propertytree.hxx"

int main (void)
{
	pt::ptree tree ;
	
	date d (2009, Dec, 16);

	tree.put ("Test.String", "Junk") ;
	tree.put ("Test.Flag", true) ;
	tree.put ("Test.Date", d) ;

	ostringstream os ;
	printTree (tree, os) ;
	cout << os.str() << endl ;

	istringstream is ;
	is.str(os.str()) ;

	pt::ptree newTree ;
	pt::read_xml (is, newTree) ;

	printTree (newTree) ;
	return 0 ;
}
