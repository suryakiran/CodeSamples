#include "std.hxx"
#include "boost-xpressive.hxx"
#include "file-reading.hxx"

#include <boost/assign/std/set.hpp>
#include <boost/assign/std/vector.hpp>
#include <boost/assign/list_inserter.hpp>
#include <boost/iterator/zip_iterator.hpp>
using namespace boost::assign ;

void fillHolidayDetails (const boost::tuple<int, const string&, const string&, const string&>& p_tuple,
						 pt::ptree& p_tree)
{
	string holiday ((format ("Holiday %1%") % p_tuple.get<0>()).str()) ;
	pt::ptree& curTree = p_tree.put_child (holiday, pt::ptree()) ;
	curTree.put ("Date", p_tuple.get<1>()) ;
	curTree.put ("Name", p_tuple.get<2>()) ;
	curTree.put ("Week", p_tuple.get<3>()) ;
}

int main (int argc, char** argv)
{
	parse_args (argc, argv) ;
	fs::fstream fin ;
	fin.open (inputFile, ios_base::in | ios_base::binary) ;

	xpr::mark_tag dateTag(1), monthTag(2), yearTag(3), nameTag(1), weekTag(1), numberTag(1) ;
	xpr::smatch results ;
	string l ;
	pt::ptree tree ;
	pt::ptree& holidaysTree = tree.put_child ("Nse.Holidays", pt::ptree()) ;

	xpr::sregex holidaysHeading =
		tdAnchor >> *_s >> "Holidays" >> *_s >> endTd ;

	xpr::sregex holidayDate =
		tdAnchor >> *_s 
		>> (dateTag= xpr::repeat<1, 2>(_d))
		>> (xpr::as_xpr("st")|"nd"|"rd"|"th") >> +_s
		>> (monthTag= longMonth) >> +_s
		>> (yearTag= xpr::repeat<4, 4>(_d)) >> *_s
		>> endTd
		;

	xpr::sregex holidayName =
		tdAnchor >> *_s
		>> (nameTag= textBeforeAnchor) >> *_s
		>> endTd
		;

	xpr::sregex holidayNumber =
		tdAnchor >> *_s 
		>> (numberTag= +_d) >> *_s
		>> endTd 
		;

	xpr::sregex holidayWeek =
		tdAnchor >> *_s 
		>> (weekTag= longWeek) >> *_s
		>> endTd 
		;

	xpr::sregex endTable =
		xpr::as_xpr('<') >> *_s >> "/table" >> *_s >> '>' ;

	bool holidaysBegin (false) ;

	vector<int> holidayNumbers ;
	vector<string> holidayNames, holidayDates, holidayWeeks ;
	int yearNum (0);

	while (getline (fin, l, '\n'))
	{
		IGNORE_BLANK_LINE(l) ;

		if (holidaysBegin)
		{
			while (getline (fin, l, '\n'))
			{
				IGNORE_BLANK_LINE(l) ;
				if (xpr::regex_match (l, results, holidayWeek))
				{
					holidayWeeks += results[weekTag] ;
					continue ;
				}
				else if (xpr::regex_match (l, results, holidayNumber))
				{
					holidayNumbers += lexical_cast<int>(results[numberTag]) ;
					continue ;
				}
				else if (xpr::regex_match (l, results, holidayDate))
				{
					yearNum = lexical_cast<int>(results[yearTag]);
					string s ((format ("%1$02d-%2%-%3%")
							% lexical_cast<int>(results[dateTag])
							% results[monthTag] % yearNum).str()) ;
					holidayDates += s ;
					continue ;
				}
				else if (xpr::regex_match (l, results, holidayName))
				{
					holidayNames += results[nameTag] ;
					continue ;
				}
				else if (xpr::regex_search (l, results, endTable))
				{
					holidaysBegin = false ;
					break ;
				}
			}
		}

		if (xpr::regex_match (l, results, holidaysHeading))
		{
			holidaysBegin = true ;
			while (getline (fin, l, '\n'))
			{
				IGNORE_BLANK_LINE(l) ;
				if (!xpr::regex_match (l, results, holidayName))
					break ;
			}
		}
	}

	holidaysTree.put("Year", yearNum);
#define BEGIN_TUPLE(vec1,vec2,vec3,vec4)\
	boost::make_tuple(vec1.begin(),vec2.begin(),vec3.begin(),vec4.begin())

#define END_TUPLE(vec1,vec2,vec3,vec4)\
	boost::make_tuple(vec1.end(),vec2.end(),vec3.end(),vec4.end())

	std::for_each (
			boost::make_zip_iterator (
				BEGIN_TUPLE (holidayNumbers, holidayDates, holidayNames, holidayWeeks)
				),
			boost::make_zip_iterator (
				END_TUPLE (holidayNumbers, holidayDates, holidayNames, holidayWeeks)
				),
			phx::bind(fillHolidayDetails, pha::arg1, phx::ref(holidaysTree))
			) ;

	pt::write_xml (cout, tree, pt::xml_writer_settings<char>(' ', 4)) ;
	fin.close() ;
}
