#include "std.hxx"
#include "boost-xpr.hxx"
#include "boost-spirit.hxx"

template <typename Iterator>
struct holidaysParser : qi::grammar<Iterator, string()> 
{
	holidaysParser() : holidaysParser::base_type (start)
	{
		myString %= *(qi::char_ - '<') ;
		tdClass %= qi::lit("<td class=\"det\">") ;

		start %=
			qi::lit("<tr") >> '>' >> qi::eol
			>> tdClass >> qi::int_ >> "</td>" >> qi::eol
			>> tdClass >> myString >> "</td>" >> qi::eol
			>> tdClass >> myString >> "</td>" >> qi::eol
			>> tdClass >> myString >> "</td>" >> qi::eol
			>> "</tr>" ;
	}

	qi::rule <Iterator, string()> start ;
	qi::rule <Iterator, string()> myString, tdClass ;
} ;

int main (void)
{
	fstream fin ;
	fin.open ("holidays-mc.html", ios_base::in) ;

	string l ;

	qi::rule <string::iterator, string()> myString, tdClass ;
	myString %= *(qi::char_ - '<') ;
	tdClass %= "<td class=\"det\">" ;

	xpr::sregex holidays =
		xpr::as_xpr (*(space)) >> "<td" >>
		*(~(xset='>')) >> '>'
		>> *(space) >> "Holidays" >> *(space) >> "</td>" ;

	xpr::smatch results ;
	string parseResult ;

	xpr::sregex hbegin = 
		xpr::as_xpr (*(space)) >> "<tr" ;

	xpr::sregex hend = 
		xpr::as_xpr (*(space)) >> "</tr" ;

	int lineNum (1) ;
	bool holidayBegin(false) ;
	while (getline (fin, l, '\n')) 
	{
		if (xpr::regex_match (l, results, holidays))
		{
			string s ;
			while(getline (fin, l, '\n'))
			{
				string::iterator lineBegin = l.begin(); 
				string::iterator lineEnd = l.end(); 
				if (xpr::regex_search(l, results, hbegin))
				{
					holidayBegin = true ;
				//	bool r = qi::phrase_parse (lineBegin, lineEnd, qi::lit("<tr") >> '>', ascii::space) ; 
				//	cout << boolalpha << l << "\tParsed: " << r << endl ;
				}

				if (holidayBegin)
				{
					bool r = qi::phrase_parse(lineBegin, lineEnd, 
							tdClass >> myString >> "</td>",
							ascii::space) ;
					if (r)
						cout << boolalpha << l << "\tParsed: " << r << endl ;
				}
#if 0
				else if (holidayBegin && xpr::regex_search(l, results, hend))
				{
					holidayBegin = false ;
					s += '\n' ;
					s += l ;
					cout << s << endl ;
					cout << "+=========================+" << endl ;
					string::iterator iterBegin = s.begin(); 
					string::iterator iterEnd = s.end(); 
					holidaysParser<string::iterator> hp ;
					bool r = qi::parse (iterBegin, iterEnd, hp, parseResult) ;
					cout << boolalpha << r << endl ;
					s.clear() ;
					break ; 
				}

				if (holidayBegin)
				{
					s += '\n' ;
					s += l ;
				}
#endif
			}
		}
	}

	fin.close () ;
}
