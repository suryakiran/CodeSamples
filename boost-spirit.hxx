#ifndef BOOST_SPIRIT_HXX
#define BOOST_SPIRIT_HXX 1

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/fusion/container.hpp>
#include <boost/format.hpp>

namespace qi = boost::spirit::qi  ;
namespace ascii = boost::spirit::ascii ;
namespace phx = boost::phoenix ;
namespace pha = phx::arg_names ;

#include <iomanip>
#include <iostream>
#include <boost/foreach.hpp>
using namespace std ;

using boost::lambda::_1 ;
using boost::lambda::_2 ;
using boost::lambda::_3 ;

using phx::push_back ;
using boost::format ;

#endif
