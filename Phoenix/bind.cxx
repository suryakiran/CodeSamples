#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

#include <boost/spirit/include/phoenix.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

using namespace std ;
using namespace boost::phoenix ;
using namespace boost::phoenix::arg_names ;
using boost::shared_ptr ;

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

		virtual void printValue (const string& s)
		{ 
			cout << "In Base: " << s << endl ; 
		}

	protected:
		string s_ ;
} ;

class TestDerived : public Test
{
	public:
		explicit TestDerived (string s) : Test(s) { }

		virtual void printValue (const string& s)
		{
			cout << "In Derived: " << s << endl ; 
		}
} ;

int main (void)
{
#if 0
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

#endif

	typedef shared_ptr<Test> TestPtr ;
	TestPtr tp = TestPtr (new TestDerived ("Surya")) ;

	boost::function <void (const string&)> func ;

	if (func.empty()) 
		cout << "Empty Function" << endl ;
	else
		cout << "Non Empty Function" << endl ;

	func = phx::bind(&Test::printValue, phx::bind(&TestPtr::operator->, tp), pha::_1) ;

	if (func.empty()) 
		cout << "Empty Function" << endl ;
	else
	{
		cout << "Non Empty Function" << endl ;
	}
	func ("Kiran") ;
}
