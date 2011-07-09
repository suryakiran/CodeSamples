#include <string> 
#include <iostream> 
#include <sstream>
#include <boost/foreach.hpp> 
#include <boost/xpressive/xpressive.hpp> 
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

using namespace std; 
namespace xpr = boost::xpressive ;
#define xset xpr::set
#define sset std::set
using namespace boost::xpressive ;
using namespace boost::algorithm ;
using boost::format ;
using boost::lexical_cast;

const string& input (
		"<tr>\n" 
		"<td class=\"det\">1</td>\n"
		"<td class=\"det\">Holiday 1</td>\n"
		"<td class=\"det\">1st January 2010</td>\n"
		"</tr>\n"
		"<tr>\n"
		"<td class=\"det\">2</td>\n"
		"<td class=\"det\">Holiday 2</td>\n"
		"<td class=\"det\">26th January 2010</td>\n"
		"</tr>\n"
		) ;

int main (void)
{
	string l ;
	istringstream is (input) ;
	smatch results ;

	mark_tag nameTag(1), dateTag(1), monthTag(2), yearTag(3) ;

	sregex trReg = 
		bos >> as_xpr("<" >> *_s >> "tr" >> *_s >> ">") ;

	sregex numReg =
		as_xpr ("<") >> *(~(xset= '>')) >> ">"
		>> *(_d) >> *_s
		>> "</td>" ;

	sregex holidayDateDetails =
		as_xpr ("<") >> *(~(xset= '>')) >> ">"
		>> (dateTag= repeat<1, 2>(_d))
		>> (as_xpr("st")|"nd"|"rd"|"th") >> *_s
		>> (monthTag= (as_xpr("January")|"February"|"March"|"April"|"May"|"June"|"July"|"August"|"September"|"October"|"November"|"December"))
		>> *_s >> (yearTag= repeat<4, 4>(_d)) >> *_s
		>> "</td>" ;

	sregex holidayName =
		as_xpr ("<") >> *(~(xset= '>')) >> ">"
		>> (nameTag= *(~(xset= '<')))
		>> "</td>" ;

	sregex combinedReg =
		numReg >> holidayName >> holidayDateDetails ;

	vector<string> dates, names ;

	while (getline (is, l, '\n'))
	{
		trim (l) ;
		// if line starts with <tr> get the next 3 lines to get the date and the
		// holiday name.
		if (regex_match (l, results, trReg)) 
		{
			string line ;
			int lineNum (0) ;
			while(getline(is, l, '\n'))
			{
				trim (l) ;
				line += l ;
				if (++lineNum == 3) break ;
			}
			if (regex_match (line, results, combinedReg))
			{
				BOOST_FOREACH (const smatch& res, results.nested_results())
				{
					if (res.regex_id() == holidayDateDetails.regex_id())
					{
						dates.push_back ((format ("%1$02d-%2%-%3%") 
							% lexical_cast<int>(res[dateTag]) % res[monthTag] % res[yearTag] 
							).str()) ;
					}
					else if (res.regex_id() == holidayName.regex_id())
						names.push_back (res[nameTag]) ;
				}

			}
			line.clear() ;
		}
	}

	return 0 ;
}
