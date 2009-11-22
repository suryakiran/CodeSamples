#include <string>
#include "spirit.hxx"

using namespace std ;

int main (void)
{
	vector<double> values ;
	cout << boolalpha ;

	const string value("123.45") ;
	double val (0.0) ;

	qi::phrase_parse (value.begin(), value.end(),
			qi::double_, ascii::space, val) ;
	cout << val << endl ;
	//const string& line ("5052.45|63.45|17021.85|236.20") ;
	//bool r = qi::phrase_parse (line.begin(), line.end(),
	//		qi::double_[push_back(phx::ref(values), qi::_1)] >> 
	//		*('|' >> qi::double_ [push_back(phx::ref(values), qi::_1)]), ascii::space) ;

	//BOOST_FOREACH (double v , values)
	//	cout << v << endl ;
	//cout << r << endl ;
//	qi::rule <string::iterator, 
	//cout << "Hello Spirit" << endl ;
}
