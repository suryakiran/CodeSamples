#ifndef BOOST_XPR_HXX
#define BOOST_XPR_HXX 1

#include <boost/xpressive/xpressive.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace xpr = boost::xpressive ;

using xpr::alnum ;
using xpr::space ;
using xpr::digit ;
using xpr::as_xpr ;
#define xset xpr::set

#endif
