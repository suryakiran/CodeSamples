#ifndef BOOST_XPRESSIVE_HXX
#define BOOST_XPRESSIVE_HXX 1

#include <boost/xpressive/xpressive.hpp>

namespace xpr = boost::xpressive ;
using xpr::alnum ;
using xpr::_s ;
using xpr::_d ;
using xpr::as_xpr ;
#define xset xpr::set

const xpr::sregex& quotedWord =
	as_xpr('"') >> *(~(xset= '"')) >> '"' ; 

const xpr::sregex& numberDelims =
	as_xpr('.')|',' ;

const xpr::sregex& textBeforeAnchor =
	as_xpr(*(~(xset= '<'))) ;

#endif
