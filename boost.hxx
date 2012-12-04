#ifndef BOOST_HXX
#define BOOST_HXX 1

#include <boost/version.hpp>

#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/assign/std.hpp>
#include <boost/iterator/zip_iterator.hpp>
#include <boost/preprocessor/cat.hpp>
#if BOOST_VERSION >= 104700
#include <boost/phoenix.hpp>
#endif
#include <boost/array.hpp>
#include <boost/current_function.hpp>

#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/range.hpp>
#include <boost/range/algorithm.hpp>

using boost::format ;
typedef boost::format fmt;
using namespace boost::assign ;

namespace str = boost::algorithm ;
namespace bl  = boost::lambda ;

#if BOOST_VERSION >= 104700
namespace phx = boost::phoenix;
namespace pha = phx::arg_names;
#endif

namespace detail {
  template <class Container, class IteratorCategory>
    struct size
    {
      size (const Container& p_container)
        : m_container(p_container) { }

      BOOST_DEDUCED_TYPENAME boost::range_difference<Container>::type
        operator() () const { return m_container.size() ; }

      private:
      const Container& m_container;
    };

  template <class Container>
    struct size <Container, std::random_access_iterator_tag>
    {
      size (const Container& p_container)
        : m_container(p_container) { }

      BOOST_DEDUCED_TYPENAME boost::range_difference<Container>::type
        operator() () const { return boost::size (m_container) ; }

      private:
      const Container& m_container;
    };
}

template <class Container>
typename boost::range_difference <Container>::type
sizeFunc (const Container& p_container)
{
  typedef BOOST_DEDUCED_TYPENAME boost::range_result_iterator<const Container>::type Iter;
  typedef BOOST_DEDUCED_TYPENAME std::iterator_traits<Iter>::iterator_category category;
  return detail::size<Container, category> (p_container)();
}

template <class FirstType, class SecondType>
ostream& operator<< (ostream& p_os, std::pair<FirstType, SecondType> p_pair)
{
  p_os << '[' << p_pair.first << ", " << p_pair.second << ']' ;
  return p_os;
}

template <class Format, class Container>
void printContainer (const Format& p_message, const Container& p_container, char p_delim=',', bool p_printSize = true)
{
	typedef BOOST_DEDUCED_TYPENAME boost::range_result_iterator<const Container>::type Iter ;
	cout << p_message ;
  if (p_printSize)
    cout << fmt (" (Size: %1%)") % sizeFunc(p_container) ;
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
