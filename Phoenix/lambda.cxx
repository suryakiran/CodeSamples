#include "std.hxx"
#include "phoenix.hxx"

void trim(string& s)
{
	boost::algorithm::trim(s) ;
}

int main (void)
{
	vector<string> vs ;

	vs.push_back (" Surya ") ;
	vs.push_back (" Kiran ") ;
	vs.push_back (" Gullapalli ") ;

	phx::for_each (pha::arg1, phx::lambda[ cout << pha::arg1 << '\n' ])(vs) ;
	cout << "===================================" << endl ;

	//std::for_each (vs.begin(), vs.end(), phx::bind(&trim, pha::arg1));
	std::for_each (vs.begin(), vs.end(), phx::bind(&str::template trim, pha::_1));
	//std::for_each (vs.begin(), vs.end(), phx::reverse(pha::arg1));

	phx::for_each (pha::arg1, phx::lambda[ cout << pha::arg1 << '\n' ])(vs) ;
	cout << "===================================" << endl ;
}
