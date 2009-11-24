#include <string>
#include "spirit.hxx"

using namespace std ;

struct Print
{
	template <typename T>
	void operator() (T& p_item) const
	{
		cout << format ("Value: -%2%-")
			% typeid(T).name() % p_item << endl ;
	}
} ;

int main (void)
{
	boost::fusion::vector<string, string, string> values ;
	cout << boolalpha ;

	const string line("Refresh Progress\nName: Surya\nCompleted: 10\nTotal: 100") ;

	qi::rule <string::const_iterator, string(), qi::skip_type> stringRule ;
	stringRule %= qi::lexeme[+(qi::char_ - qi::eol)] ;

	qi::rule<string::const_iterator, boost::fusion::vector<string, string, string>(), 
		qi::skip_type> r ;
	r %= qi::lit("Refresh Progress") >> qi::eol >>
		qi::lit("Name: ") >> stringRule >> qi::eol >>
		qi::lit("Completed: ") >> stringRule >> qi::eol >>
		qi::lit("Total: ") >> stringRule ;

	qi::phrase_parse (line.begin(), line.end(), r, ascii::space, values) ; 

	boost::fusion::for_each (values, Print()) ;
}
