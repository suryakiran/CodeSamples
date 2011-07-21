#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/container.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

namespace qi = boost::spirit::qi  ;
namespace ascii = boost::spirit::ascii ;
namespace phx = boost::phoenix ;

#include <iostream>
#include <vector>
#include <string>
using namespace std ;

typedef vector<string> StringVector ;
typedef vector<double> DoubleVector ;

string testString("\"String1\",\"String2\",\"String3\",\"63.35\",\"63.50\",\"64.45\",\"62.55\",\"63.60\"") ;

struct TestStruct
{
	StringVector strings ;
	DoubleVector numbers ;
} ;


BOOST_FUSION_ADAPT_STRUCT(
	TestStruct,
	(StringVector, strings)
	(DoubleVector, numbers)
	)

int main (int argc, char** argv)
{
	qi::rule<string::iterator, string(), ascii::space_type> stringWithQuotes
		= qi::lexeme['"' >> +(qi::char_ - '"') >> '"'] ;

	qi::rule<string::iterator, DoubleVector(), ascii::space_type> quotedDoubles =
		qi::skip(ascii::space)[qi::lit('"') >> qi::double_ >> '"'] % ',' ;

	qi::rule<string::iterator, TestStruct(), ascii::space_type> stringsAndDoubles =
		qi::repeat(3)[stringWithQuotes >> ','] >> quotedDoubles ;

	TestStruct testStruct ;

	string::iterator iterBegin = testString.begin() ;
	string::iterator iterEnd = testString.end() ;

	if (qi::phrase_parse(iterBegin, iterEnd, stringsAndDoubles, ascii::space, testStruct))
	{
		cout << "Strings: " << testStruct.strings.size() << endl ;
		cout << "Numbers: " << testStruct.numbers.size() << endl ;
	}
}
