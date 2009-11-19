#include <iostream>

#include <boost/preprocessor.hpp>
#include <boost/fusion/container.hpp>
using namespace std ;
using namespace boost ;

#define MAX_ARGS 5

template <int id, BOOST_PP_ENUM_PARAMS(MAX_ARGS, typename T)>
void func (const boost::fusion::vector<BOOST_PP_ENUM_PARAMS(MAX_ARGS, T)> p_args)
{
	cout << "Multiple Arguments: id " << id << endl ;
}

template<int id>
void func (void)
{
	cout << "No arguments: id " << id << endl ;
	func <id>(boost::fusion::make_vector()) ;
}

int main (void)
{
	func<10> (boost::fusion::make_vector(1, 2)) ;
	func<6> () ;

	return 0 ;
}

