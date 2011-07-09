#include <iostream>

#include <boost/format.hpp>
#include <boost/signals2.hpp>
#include <boost/spirit/home/phoenix/bind/bind_member_function.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>

using namespace std ;
using namespace boost::signals2 ;
using boost::format ;

namespace phx = boost::phoenix ;
namespace pha = phx::arg_names ;

struct Temp
{
	void zeroArgs () const
	{
		cout << "-No Args-" << endl ;
	}

	void oneArg (const int i) const
	{
		cout << format("One Arg: (%1%)") % i << endl ;
	}

	void twoArgs (const int i, const int j) const
	{
		cout << format("Two Args: (%1%, %2%)") % i % j << endl ;
	}

	void threeArgs (const int i, const int j, const int k) const
	{
		cout << format("Three Args: (%1%, %2%, %3%)") % i % j % k << endl ;
	}

	void fiveArgs (const int a, const int b, const int c, const int d, const int e) const
	{
		cout << 
			format("Five Args: (%1%, %2%, %3%, %4%, %5%)") 
			% a % b % c % d % e << endl ;
	}
} ;

int main (void)
{
	signal <void()> sig_0 ;
	signal <void(int)> sig_1 ;
	signal <void(int, int)> sig_2 ;
	signal <void(int, int, int)> sig_3 ;
	signal <void(int, int, int, int, int)> sig_5 ;

	Temp t ;
	sig_0.connect (phx::bind(&Temp::zeroArgs, t)) ;
	sig_0() ;

	sig_1.connect(phx::bind(&Temp::oneArg, t, pha::arg1)) ;
	sig_1(5) ;

	sig_2.connect(phx::bind(&Temp::twoArgs, t, pha::_1, pha::_2)) ;
	sig_2(5, 10) ;

	sig_3.connect(phx::bind(&Temp::threeArgs, t, pha::_1, pha::_2, pha::_3)) ;
	sig_3(5, 10, 15) ;

	sig_5.connect(phx::bind(&Temp::fiveArgs, t, pha::arg1, pha::arg2, pha::arg3, pha::arg4, pha::arg5)) ;
	sig_5(5, 10, 15, 20, 25) ;
}
