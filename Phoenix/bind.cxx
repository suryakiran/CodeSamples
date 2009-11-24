#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

#include <boost/spirit/include/phoenix.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>

using namespace std ;
using namespace boost::phoenix ;
using namespace boost::phoenix::arg_names ;

namespace phx = boost::phoenix ;
namespace pha = boost::phoenix::arg_names ;
namespace bll = boost::lambda ;

class Test
{
	friend ostream& operator<< (ostream& os, const Test& p)
	{
		os << "Test Value: " << p.s_ ;
		return os ;
	}
	public:
		explicit Test(string s) : s_(s) { }
		void setValue (string s) { s_ = s ; }
		string getValue () { return s_ ; }

		string getValue (const string& s) 
		{
			if (s == "surya") return s_ ;
			else return "Junk" ;
		}

	private:
		string s_ ;
} ;

int main (void)
{
	vector<Test> vt ;
	vt.push_back (Test("surya")) ;
	vt.push_back (Test("kiran")) ;
	vt.push_back (Test("abc")) ;
	vt.push_back (Test("def")) ;
	vt.push_back (Test("ghi")) ;

	typedef string (Test::*fp) (const string& s) ;
	fp fun = &Test::getValue ;

	vector<Test>::iterator iter = std::find_if (vt.begin(), vt.end(),
		phx::bind(fun, pha::arg1, "ZZ") == "surya") ;

	if (iter == vt.end())
		cout << "No Result" << endl ;
	else
		cout << *iter << endl ;

#if 0
	std::for_each (vt.begin(), vt.end(),
			phx::bind(&Test::getValue, pha::arg1)
	) ;

	std::for_each (vt.begin(), vt.end(),
			bll::bind(&Test::getValue, bll::_1)
			) ;
#endif
}
