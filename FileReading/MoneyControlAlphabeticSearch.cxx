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

	pt::ptree tree ;
	pt::ptree& searchTree = tree.put_child ("Money Control Search", pt::ptree()) ;
	xpr::smatch results ;
	string l ;

	xpr::mark_tag sectorTag(1), codeTag(2), nameTag(3) ;
	xpr::sregex codeReg = 
		as_xpr("<td") >> *(~(xset= '<')) >> '<'
		>> "a class" >> *(~_s) >> _s
		>> "href=" >> (xset='\'','"')
		>> "http://www.moneycontrol.com/india/stockpricequote/"
		>> (sectorTag= +(xpr::alnum|'-')) >> '/' >> *(~(xset= '/')) >> '/' >> (codeTag= +xpr::alnum)
		>> *(~(xset= '>')) >> '>' >> *_s 
		>> (nameTag= +(xpr::alnum|_s|'-')) >> as_xpr('<') ;
		;

	while (getline (fin, l, '\n'))
	{
		IGNORE_BLANK_LINE(l) ;

		if (xpr::regex_search (l, results, codeReg))
		{
			string sector = camelCase(results[sectorTag]) ;
			string name = camelCase(results[nameTag]) ;
			string code = results[codeTag] ;

			pt::ptree& curTree = searchTree.put_child (code, pt::ptree()) ;
			curTree.put ("Name", name) ;
			curTree.put ("Sector", sector) ;
		}
	}
	pt::write_xml (cout, tree, pt::xml_writer_settings<char>(' ', 4)) ;
	fin.close() ;
}
