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
	pt::ptree& codesTree = tree.put_child ("Money Control.Codes", pt::ptree()) ;
	xpr::smatch results ;
	string l ;

	xpr::mark_tag secTag(1), codeTag(2), nameTag(3), indexTag(1);
	xpr::sregex codesReg =
		xpr::as_xpr("href=") >> (xset='\'','"') >> "/india/stockpricequote/" >>
		(secTag= +alnum) >> '/' >> +alnum >> '/' >> (codeTag= +alnum)
		>> *(~(xset= '<')) >> xpr::icase("<b>") >> (nameTag= *(~(xset= '<'))) ;

	xpr::sregex indexCodes =
		xpr::as_xpr(':') >> *_s >> endTag("b", false)
		>> !(indexTag= as_xpr(*(~(xset= '<','(',')'))))
		>> (xset='<',')','(')
		;

	while (getline (fin, l, '\n'))
	{
		IGNORE_BLANK_LINE(l) ;
		str::erase_all(l, "&nbsp;");

		if (xpr::regex_search (l, results, codesReg))
		{
			string name = camelCase(results[nameTag]) ;
			string sector = results[secTag] ;
			string code = results[codeTag] ; 

			pt::ptree& curTree = codesTree.put_child (code, pt::ptree()) ;
			curTree.put ("Name", name) ;
			curTree.put ("Sector", sector) ;

			while(getline(fin, l, '\n'))
			{
				IGNORE_BLANK_LINE(l);
				str::erase_all(l, "&nbsp;");
				if (xpr::regex_search (l, results, indexCodes))
				{
					xpr::sregex_iterator regIter (l.begin(), l.end(), indexCodes);
					xpr::sregex_iterator regIterEnd;
					while (regIter != regIterEnd)
					{
						const xpr::smatch& results = *regIter;
						if (curTree.find("Bse") == curTree.not_found())
							curTree.put("Bse", results[indexTag]);
						else if (curTree.find("Nse") == curTree.not_found())
							curTree.put("Nse", results[indexTag]);
						else
							curTree.put("Isin", results[indexTag]);
						++regIter;
					}
					break;
				}
			}
		}

	}

	pt::write_xml (cout, tree, pt::xml_writer_settings<char>(' ', 4)) ;
	fin.close() ;
}
