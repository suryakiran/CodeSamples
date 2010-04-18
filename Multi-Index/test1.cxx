#include <iostream>
#include <string>
using namespace std ;

#define BOOST_MULTI_INDEX_LIMIT_INDEXED_BY_SIZE 5
#define BOOST_MULTI_INDEX_LIMIT_TAG_SIZE 3
#define BOOST_MULTI_INDEX_LIMIT_COMPOSITE_KEY_SIZE 5 

#include <Common/mic_visualizer.hpp>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>

#include <boost/foreach.hpp>
#include <boost/typeof/typeof.hpp>
using namespace boost ;
using namespace boost::multi_index ;


class Test
{
	friend bool operator< (const Test& p_lhs, const Test& p_rhs)
	{ return p_lhs._i < p_rhs._i ; }

	friend ostream& operator << (ostream& os, const Test& p_test)
	{
		os << "Integer: " << p_test._i << "\tString: " << p_test._s ; 
		return os ;
	}

	private:
		int _i ;
		string _s ;

	public:
		Test (int i, string s): _i(i), _s(s) { }

		string getString (void) const { return _s ; }
} ;

struct byNumber { } ;
struct byString { } ;

typedef
multi_index_container <Test, indexed_by <
ordered_unique<tag<byNumber>, identity <Test> >
, ordered_non_unique < tag<byString>, BOOST_MULTI_INDEX_CONST_MEM_FUN(Test, string, getString) >
> > Container ;

VISUALIZE_MULTI_INDEX_CONTAINER(Container);

int main (void)
{
	typedef Container::index<byNumber>::type TestByNumber ;
	typedef Container::index<byString>::type TestByString ;

	Container c ;

	c.insert (Test(5, "Surya")) ;
	c.insert (Test(15, "Kiran")) ;

	//TestByNumber& tests = c.get<byNumber>() ;
	BOOST_AUTO(&tests, c.get<byNumber>()) ;

	BOOST_FOREACH (Test t, tests)
		cout << t << endl ;

	return 0 ;
}
