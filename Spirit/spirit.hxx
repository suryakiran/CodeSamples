#ifndef SPIRIT_HXX
#define SPIRIT_HXX 1

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/lambda/lambda.hpp>

namespace qi = boost::spirit::qi  ;
namespace ascii = boost::spirit::ascii ;
namespace phx = boost::phoenix ;

#include <iomanip>
#include <iostream>
#include <boost/foreach.hpp>
using namespace std ;

using boost::lambda::_1 ;
using boost::lambda::_2 ;
using boost::lambda::_3 ;

using phx::push_back ;

#endif
