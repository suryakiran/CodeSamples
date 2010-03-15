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

	xpr::smatch results ;
	string l ;
	pt::ptree tree ;
	pt::ptree& codesTree = tree.put_child ("From Money Control.Codes", pt::ptree()) ;

	xpr::mark_tag bseTag(1), nseTag(2), isinTag(3), sectorTag(4), codeTag(1) ;

	xpr::sregex mcCodeReg =
		xpr::as_xpr("setTimeout") >> *_s >> '(' >> *_s
		>> anyQuote >> "window.location" >> *_s >> '=' >> *_s
		>> anyQuote >> "http://www.moneycontrol.com/india/stockpricequote/"
		>> (sectorTag= *(~(xset= '/'))) >> '/'
		>> *(~(xset= '/')) >> '/' // Name
		>> (codeTag= *(~(xset='\'','"')))
		;
#if 0
	xpr::sregex mcCodeReg =
		xpr::as_xpr("/stocks/company_info/tech_charting.php?sc_did=") 
		>> (codeTag= *(~(xset= '&')))
		;
#endif

	xpr::sregex codesReg =
		xpr::as_xpr("BSE:") >> *_s >> skipAnchor >> *_s 
		>> (bseTag= *(~_s)) >> textBeforeAnchor
		>> skipAnchor >> *_s >> "NSE:" >> *_s >> skipAnchor >> *_s
		>> (nseTag= *(~_s)) >> textBeforeAnchor >> skipAnchor 
		>> *_s >> "ISIN:" >> *_s >> skipAnchor >> *_s
		>> (isinTag= *(~_s)) >> textBeforeAnchor 
		;

	while (getline (fin, l, '\n'))
	{
		IGNORE_BLANK_LINE(l) ;
		
		if (xpr::regex_search (l, results, codesReg))
		{
			codesTree.put ("Bse Code", results[bseTag]) ;
			codesTree.put ("Nse Code", results[nseTag]) ;
			codesTree.put ("Isin Code", results[isinTag]) ;
		}

		if (xpr::regex_search (l, results, mcCodeReg))
		{
			codesTree.put("Mc Code", results[codeTag]) ;
			codesTree.put("Sector", results[sectorTag]) ;
		}
	}

	pt::write_xml (cout, tree, pt::xml_writer_settings<char>(' ', 4)) ;
	fin.close() ;
}
