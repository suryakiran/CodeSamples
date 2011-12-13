#ifndef BOOST_HXX
#define BOOST_HXX 1

#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/assign/std/vector.hpp>
#include <boost/assign/std/list.hpp>
#include <boost/assign/list_inserter.hpp>
#include <boost/iterator/zip_iterator.hpp>
#include <boost/preprocessor/cat.hpp>

#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/range.hpp>

using boost::format ;
typedef boost::format fmt;
using namespace boost::assign ;

namespace str = boost::algorithm ;
namespace bl  = boost::lambda ;

template <class Format, class Container>
void printContainer (const Format& p_message, const Container& p_container, char p_delim=',', bool p_printSize = true)
{
	typedef BOOST_DEDUCED_TYPENAME boost::range_result_iterator<const Container>::type Iter ;
	cout << p_message ;
  if (p_printSize)
    cout << fmt (" (Size: %1%)") % boost::size(p_container) ;
  cout << endl;
	Iter beginIter (boost::begin(p_container)), endIter (boost::end(p_container)) ;
	for (Iter iter = beginIter; iter != endIter; ++iter) 
	{
		if (iter != beginIter) cout << p_delim ;
		cout << *iter ;	
	}
	cout << endl ;
}

#endif
