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
	pt::ptree& indexTree = tree.put_child ("From Money Control.Bse Indices", pt::ptree()) ;

	xpr::mark_tag indexTag (1), valueTag(1), profitTag(1), profitValue(2) ;
	xpr::sregex indexReg =
		beginTd >> "class" >> *_s >> '=' >> "\"bl_12\"" >> *_s >> '>'
		>> aHref >> "javascript" >> textBeforeCloseAnchor >> "><u>"
		>> (indexTag= textBeforeAnchor)
		;

	xpr::sregex valueReg =
		as_xpr("<td align") >> *_s >> '=' >> *_s >> quotedWord >> *_s 
		>> "class" >> *_s >> '=' >> *_s >> quotedWord >> *_s >> '>'
		>> (valueTag = *(_d | numberDelims)) >> *_s >> endTd
		;

	xpr::sregex profitLossReg =
		as_xpr("<td align") >> *_s >> '=' >> *_s >> quotedWord >> *_s
		>> "class" >> *_s >> '=' >> *_s >> (profitTag= quotedWord) >> *_s >> '>'
		>> (profitValue = *(_d | numberDelims)) >> *_s >> endTd
		;

	while (getline (fin, l, '\n'))
	{
		IGNORE_BLANK_LINE(l) ;

		if (xpr::regex_search (l, results, indexReg))
		{
			string idx (results[indexTag]) ;
			pt::ptree& curTree = indexTree.put_child (idx, pt::ptree()) ;

			string dummy ("") ;
			l = getTDline (fin, dummy) ;
			if (xpr::regex_search (l, results, valueReg))
			{
				curTree.put ("Current Price", results[valueTag]) ;
			}
			l = getTDline (fin, dummy) ;
			if (xpr::regex_search (l, results, profitLossReg))
			{
				string profitColor (results[profitTag]) ;
				str::erase_all (profitColor, "\"") ;
				double factor (1.0), price (0.0) ;
				if (str::starts_with(profitColor, "r-"))
					factor = -1.0 ;
				try { price = factor * lexical_cast<double>(results[profitValue]) ; }
				catch (...) { }
				curTree.put ("Change", price) ;
			}
		}

	}

	pt::write_xml (cout, tree, pt::xml_writer_settings<char>(' ', 4)) ;
	fin.close() ;
}
