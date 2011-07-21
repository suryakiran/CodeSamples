#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::cout ;
using std::endl ;

#include <boost/algorithm/string/trim.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace phx = boost::phoenix ;
namespace pha = phx::arg_names ;
namespace str_algo = boost::algorithm ;

void trim(std::string& s)
{
	str_algo::trim(s) ;
}

int main (void)
{
	std::vector<std::string> vs ;

	vs.push_back (" String1 ") ;
	vs.push_back (" String2 ") ;
	vs.push_back (" String3 ") ;

	phx::for_each (pha::arg1, phx::lambda[ cout << pha::arg1 << '\n' ])(vs) ;
	cout << "===================================" << endl ;

	// What I'm trying to do is call boost::algorithm::trim on all elements of vector.
	// the below given statement works without any problem.

	void (*pf) (std::string&) = &str_algo::trim<std::string> ;
	std::for_each (vs.begin(), vs.end(), phx::bind(pf, pha::arg1));
	
	//How do I call boost::algorithm::trim directly using Boost.Phoenix or Boost.Lambda. Below
	//I'm trying to do it using phoenix.
	//std::for_each (vs.begin(), vs.end(), phx::bind(&str_algo::template trim, pha::_1));
	
	phx::for_each (pha::arg1, phx::lambda[ cout << pha::arg1 << '\n' ])(vs) ;
	cout << "===================================" << endl ;
}
