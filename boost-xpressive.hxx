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
	as_xpr('.')|','|'-' ;

const xpr::sregex& textBeforeAnchor =
	as_xpr(*(~(xset= '<'))) ;

const xpr::sregex& textBeforeCloseAnchor =
	as_xpr(*(~(xset= '>'))) ;

const xpr::sregex& skipAnchor =
	as_xpr('<') >> *(~(xset= '>')) >> '>' ;

const xpr::sregex& anyQuote =
		(xset='\'','"') ;

const xpr::sregex& endA =
	as_xpr('<') >> *_s >> "/a" >> *_s >> '>' ;

const xpr::sregex& beginTr =
	as_xpr('<') >> *_s >> "tr" >> *_s >> '>' ;

const xpr::sregex& endTr =
	as_xpr('<') >> *_s >> "/tr" >> *_s >> '>' ;

const xpr::sregex& beginTd =
	as_xpr('<') >> *_s >> "td" >> +_s ;

const xpr::sregex& boldBegin =
	as_xpr('<') >> *_s >> 'b' >> *_s >> '>';

const xpr::sregex& boldEnd =
	as_xpr('<') >> *_s >> "/b" >> *_s >> '>';

const xpr::sregex& endTd =
	as_xpr('<') >> *_s >> "/td" >> *_s >> '>' ;

const xpr::sregex& beginTh =
	as_xpr('<') >> *_s >> "th" >> +_s >> textBeforeCloseAnchor >> '>' ;

const xpr::sregex& endTh =
	as_xpr('<') >> *_s >> "/th" >> *_s >> '>' ;

const xpr::sregex& closeAnchor =
	as_xpr(*_s) >> '>' >> *_s ;

const xpr::sregex& tdAnchor =
	beginTd >> *(~(xset= '>')) >> '>' ;

const xpr::sregex& aHref =
	as_xpr ('<') >> *_s >> 'a' >> +_s >> "href" >> *_s >> '=' >> *_s >> anyQuote >> *_s;

const xpr::sregex& number =
	as_xpr(+(_d|numberDelims)) ;

const xpr::sregex& floatNumber =
		!(xset= '-','+') >> +_d >> !(xset='.') >> xpr::repeat<0,2>(_d);

const xpr::sregex& longMonth =
	as_xpr("January")|"February"|"March"|"April"|"May"|"June"|"July"|"August"|"September"|"October"|"November"|"December" ;

const xpr::sregex& shortMonth =
	as_xpr("Jan")|"Feb"|"Mar"|"Apr"|"May"|"Jun"|"Jul"|"Aug"|"Sep"|"Oct"|"Nov"|"Dec" ;

const xpr::sregex& shortMonthU =
	as_xpr("JAN")|"FEB"|"MAR"|"APR"|"MAY"|"JUN"|"JUL"|"AUG"|"SEP"|"OCT"|"NOV"|"DEC" ;

const xpr::sregex& longWeek =
	as_xpr ("Sunday")|"Monday"|"Tuesday"|"Wednesday"|"Thursday"|"Friday"|"Saturday" ;

#endif
