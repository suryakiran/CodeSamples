#include "std.hxx"
#include "file-reading.hxx"
#include "boost-xpressive.hxx"

#include <boost/assign/std/set.hpp>
#include <boost/assign/std/map.hpp>
#include <boost/assign/list_inserter.hpp>
using namespace boost::assign ;

#include <boost/iterator/zip_iterator.hpp>

int main (int argc, char** argv)
{
	parse_args (argc, argv) ;
	fs::fstream fin ;
	fin.open (inputFile, ios_base::in | ios_base::binary) ;
	pt::ptree tree ;
	string l ;

	pt::ptree& nsePrices = tree.put_child("Scrip.Price Details.Nse", pt::ptree());
	pt::ptree& bsePrices = tree.put_child("Scrip.Price Details.Bse", pt::ptree());

	map<string, string> fieldMap;
	insert (fieldMap) 
		("Last Traded Price", "CurrentPrice")
		("Day's Open", "DayOpen") ("Day's High", "DayHigh") ("Day's Low", "DayLow")
		("High", "YearHigh") ("Low", "YearLow")
		("Previous Close", "PreviousDayClose")
		;

	vector<string> highLowPriceOrder ;
	highLowPriceOrder += "YearHigh", "YearLow";

	xpr::mark_tag nameTag(1), numTag(1) ;
	xpr::smatch results ;

	xpr::sregex nameReg =
		as_xpr("<td class") >> *_s >> "=" >> *_s >> "TopHeading" >> *_s
		>> "Colspan" >> *_s >> "=" >> +_d >> *_s >> "nowrap" >> *_s >> ">"
		>> (nameTag= +(alnum|(xset=' ','(',')'))) >> *(~(xset= '<')) >> "</td>" 
		;

	xpr::sregex priceTypeReg =
		beginTd >> "nowrap" >> textBeforeCloseAnchor >> '>'
		>> (nameTag= *(~(xset[xpr::range('0','9')|'>']))) >> endTd
		;

	xpr::sregex priceReg =
		beginTd >> "nowrap" >> textBeforeCloseAnchor >> '>'
		>> *_s >> (numTag= floatNumber) >> *_s >> endTd
		;

	xpr::sregex highLowPriceReg =
		beginTd >> "align" >> textBeforeCloseAnchor >> '>'
		>> *_s >> (numTag= floatNumber) >> *_s >> endTd
		;

	bool typeFound (false);
	string key;

	while (getline(fin, l, '\n'))
	{
		IGNORE_BLANK_LINE(l) ;
		str::erase_all(l, "&nbsp;");

		if (xpr::regex_match (l, results, nameReg))
		{
			cout << results[nameTag] << endl ;
			continue ;
		}

		if (typeFound && xpr::regex_match (l, results, priceReg))
		{
			double num (lexical_cast<double>(results[numTag]));
			if (bsePrices.find(key) == bsePrices.not_found())
				bsePrices.put(key, num) ;
			else
				nsePrices.put(key, num);
			continue ;
		}
		else if (xpr::regex_match(l, results, highLowPriceReg))
		{
			double num (lexical_cast<double>(results[numTag]));
			bool priceSet (false);
			BOOST_FOREACH(string cur, highLowPriceOrder)
			{
				if (bsePrices.find(cur) == bsePrices.not_found())
				{
					bsePrices.put(cur, num) ;
					priceSet = true;
					break;
				}
				else
					continue;
			}

			if (priceSet) continue;
			BOOST_FOREACH(string cur, highLowPriceOrder)
			{
				if (nsePrices.find(cur) == nsePrices.not_found())
				{
					nsePrices.put(cur, num) ;
					break;
				}
				else
					continue;
			}
		}

		if (xpr::regex_match (l, results, priceTypeReg))
		{
			string priceType (results[nameTag]);
			if (fieldMap.count(priceType))
			{
				key = fieldMap[priceType];
				typeFound = true;
			}
			else 
				typeFound = false;
			continue ;
		}
	}

	pt::write_xml (cout, tree, pt::xml_writer_settings<char>(' ', 4)) ;

	return 0 ;
}
