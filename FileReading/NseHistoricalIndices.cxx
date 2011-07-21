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

	xpr::mark_tag siteTag(1) ;
	xpr::sregex csvFile = 
		aHref 
		>> (siteTag= *(~(xset= '\'','"')))
		>> textBeforeCloseAnchor >> '>' >> *_s 
		>> "Download file in csv format"
		;

	while (getline (fin, l, '\n'))
	{
		IGNORE_BLANK_LINE(l) ;
		if (xpr::regex_search (l, results, csvFile))
		{
			tree.put("Nse Indices Historical Data Csv File", results[siteTag]) ;
			break ;
		}
	}

	pt::write_xml (cout, tree, pt::xml_writer_settings<char>(' ', 4)) ;
	fin.close() ;
}
