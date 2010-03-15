#ifndef BOOST_HXX
#define BOOST_HXX 1

#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/assign/std/vector.hpp>
#include <boost/assign/std/list.hpp>

#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/range.hpp>

using boost::format ;
using namespace boost::assign ;

namespace str = boost::algorithm ;
namespace bl  = boost::lambda ;

template <class Container>
void printContainer (const std::string& p_message, const Container& p_container)
{
	typedef BOOST_DEDUCED_TYPENAME boost::range_result_iterator<const Container>::type Iter ;
	cout << p_message << endl ;
	for (Iter iter = boost::begin(p_container); iter != boost::end(p_container); ++iter) {
		cout << "\t-" << *iter ;
	}
	cout << endl ;
}

#endif
