#include "std.hxx"
#include "file-reading.hxx"
#include "boost-xpressive.hxx"

#include <boost/assign/std/set.hpp>
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

	xpr::mark_tag nameTag(1) ;
	xpr::smatch results ;

	xpr::sregex nameReg =
		as_xpr("<td class") >> *_s >> "=" >> *_s >> "TopHeading" >> *_s
		>> "Colspan" >> *_s >> "=" >> +_d >> *_s >> "nowrap" >> *_s >> ">"
		>> (nameTag= +(alnum|(xset=' ','(',')'))) >> *(~(xset= '<')) >> "</td>" 
		;

	xpr::sregex priceReg =
		as_xpr("<td nowrap>") >> "&nbsp;" >> +(_d | numberDelims) >> "</td>" ;

	xpr::sregex priceTypeReg =
		as_xpr("<td nowrap align=") >> quotedWord >> '>'
		>> textBeforeAnchor >> "</td>" ;

	while (getline(fin, l, '\n'))
	{
		IGNORE_BLANK_LINE(l) ;

		if (xpr::regex_match (l, results, nameReg))
			cout << results[nameTag] << endl ;

		if (xpr::regex_match (l, results, priceTypeReg))
			cout << l << endl ;
	}

	pt::write_xml (cout, tree, pt::xml_writer_settings<char>(' ', 4)) ;

	return 0 ;
}
