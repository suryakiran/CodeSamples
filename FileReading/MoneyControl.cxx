#include "std.hxx"
#include "boost-xpressive.hxx"
#include "file-reading.hxx"

#include <boost/assign/std/set.hpp>
#include <boost/assign/list_inserter.hpp>
using namespace boost::assign ;

int main (int argc, char** argv)
{
	parse_args (argc, argv) ;
	fs::fstream fin ;
	fin.open (inputFile, ios_base::in | ios_base::binary) ;

	set<string> ignoreFields ;
	insert (ignoreFields) ("Vol") ;

	xpr::smatch results ;
	string l ;

	xpr::mark_tag textTag(1), priceTag(1) ;
	pt::ptree tree ;
	pt::ptree& nsePrices = tree.put_child ("Scrip.PriceDetails.Nse", pt::ptree()) ;
	pt::ptree& bsePrices = tree.put_child ("Scrip.PriceDetails.Bse", pt::ptree()) ;

	xpr::sregex overview =
		as_xpr("<b>") >> *_s >> "Overview" >> *_s >> "</b>" ;

	xpr::sregex validText =
		as_xpr(*(~(xset= '<','&',';'))) ;

	xpr::sregex td =
		as_xpr("<td class") >> *_s >> "=" >> *_s >> "\"hed\"" >> '>'
		>> (textTag= validText) >> "</td>" ;

	xpr::sregex price =
		as_xpr("<td") >> *(~(xset= '>')) >> '>' >> *_s
		>> (priceTag = +(_d|numberDelims)) ;

	bool priceDetailsBegin (false) ;
	bool bseDetails (true) ;
	while (getline (fin, l, '\n'))
	{
		IGNORE_BLANK_LINE(l) ;

		if (xpr::regex_search (l, results, overview))
			priceDetailsBegin = true ;

		if (!priceDetailsBegin)
			continue ;

		if (xpr::regex_match (l, results, td))
		{
			string field (results[textTag]) ;
			if (!ignoreFields.count(field))
			{
				while (getline (fin, l, '\n'))
				{
					IGNORE_BLANK_LINE(l) ;
					if (regex_search (l, results, price))
					{
						string s (results[priceTag]) ;
						str::erase_all (s, ",") ;
						if (bseDetails)
						{
							bsePrices.put(field, lexical_cast<double>(s)) ;
							bseDetails = false ;
						}
						else
						{
							nsePrices.put(field, lexical_cast<double>(s)) ;
							bseDetails = true ;
						}

						break ;
					}
				}
			}
		}
	}

	pt::write_xml (cout, tree, pt::xml_writer_settings<char>(' ', 4)) ;
	fin.close() ;
}
