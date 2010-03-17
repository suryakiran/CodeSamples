#include "std.hxx"
#include "boost-xpressive.hxx"
#include "file-reading.hxx"

#include <boost/assign/std/set.hpp>
#include <boost/assign/std/vector.hpp>
#include <boost/assign/list_inserter.hpp>
#include <boost/iterator/zip_iterator.hpp>
using namespace boost::assign ;

int main (int argc, char** argv)
{
	parse_args (argc, argv) ;
	fs::fstream fin ;
	fin.open (inputFile, ios_base::in | ios_base::binary) ;

	string l ;
	pt::ptree tree ;
	xpr::smatch results ;

	xpr::mark_tag valueTag (1), displayTag(2) ;
	xpr::sregex optionReg =
		xpr::as_xpr ('<') >> "option" >> +_s >> "value" >> *_s >> '=' >> *_s
		>> (valueTag= *(~(xset='>','"'))) >> '>'
		>> (displayTag= textBeforeAnchor) >> *_s 
		>> '<' >> *_s >> "/option" >> *_s >> '>'
		;

	while (getline (fin, l, '\n'))
	{
		IGNORE_BLANK_LINE(l) ;
		if (xpr::regex_search (l, results, optionReg))
		{
			xpr::sregex_iterator regIter (l.begin(), l.end(), optionReg) ;
			xpr::sregex_iterator regIterEnd ;
			int num(0) ;
			for (; regIter != regIterEnd; ++regIter)
			{
				results = *regIter ;
				string inum ((format ("Bse Indices.Index %1%") % ++num).str()) ;
				pt::ptree& curTree = tree.put_child (inum, pt::ptree()) ;
				curTree.put ("Value", results[valueTag]) ;
				curTree.put ("Display", results[displayTag]) ;
			}
		}
	}

	pt::write_xml (cout, tree, pt::xml_writer_settings<char>(' ', 4)) ;
	fin.close() ;
}
