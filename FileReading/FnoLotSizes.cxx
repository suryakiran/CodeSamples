#include "std.hxx"
#include "boost-xpressive.hxx"
#include "file-reading.hxx"
#include "boost-spirit.hxx"

#include <boost/assign/std/set.hpp>
#include <boost/assign/std/vector.hpp>
#include <boost/assign/list_inserter.hpp>
#include <boost/iterator/zip_iterator.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
using namespace boost::assign ;

typedef vector<string> StringVector ;
typedef vector<double> DoubleVector ;
typedef vector<int> IntVector ;

struct LotsDetails
{
	StringVector headings ; 
	IntVector lots ;
};

BOOST_FUSION_ADAPT_STRUCT (
	LotsDetails,
	(StringVector, headings)
	(IntVector, lots)
	)

int main (int argc, char**argv)
{
	parse_args (argc, argv) ;
	fs::fstream fin ;
	fin.open (inputFile, ios_base::in | ios_base::binary) ;

	string l ;
	pt::ptree tree ;

	typedef boost::tuple <StringVector, IntVector> LotsTuple ;

	qi::rule<string::iterator, vector<string>(), ascii::space_type> indexHeadingsLine = 
		qi::lit("UNDERLYING") >> ',' >> +(qi::char_ - ',') % ',' ;

	qi::rule<string::iterator, vector<string>(), ascii::space_type> nonIndexHeadingsLine = 
		qi::lit("Derivatives on Individual Securities") >> ',' >> +(qi::char_ - ',') % ',' ;

	qi::rule<string::iterator, LotsDetails(), ascii::space_type> lots =
		qi::repeat(2)[qi::lexeme[+(qi::char_ - ',')] >> ','] >> qi::repeat(3)[qi::int_ >> ','];

	pt::ptree& indexTree = tree.put_child ("Lot Sizes.Indices", pt::ptree()) ; 
	pt::ptree& nonIndexTree = tree.put_child ("Lot Sizes.Non Indices", pt::ptree()) ; 

	StringVector indexHeadings, nonIndexHeadings; 
	LotsDetails indexLotsDetails, nonIndexLotsDetails ; 
	bool indexLots (false) ;

	while (getline (fin, l, '\n'))
	{
		IGNORE_BLANK_LINE(l) ;

		string::iterator iterBegin = l.begin() ;
		string::iterator iterEnd = l.end() ;

		if (qi::phrase_parse (iterBegin, iterEnd, indexHeadingsLine, ascii::space, indexHeadings))
		{
			indexLots = true ;
			BOOST_FOREACH (string& s, indexHeadings)
				str::trim (s) ;
			continue ;
		}
		if (qi::phrase_parse (iterBegin, iterEnd, nonIndexHeadingsLine, ascii::space, nonIndexHeadings))
		{
			indexLots = false ;
			BOOST_FOREACH (string& s, nonIndexHeadings)
				str::trim (s) ;
			continue ;
		}

		StringVector& headings = indexLots ? indexHeadings : nonIndexHeadings ;
		LotsDetails& det = indexLots ? indexLotsDetails : nonIndexLotsDetails ;

		if (qi::phrase_parse (iterBegin, iterEnd, lots, ascii::space, det))
		{
			BOOST_FOREACH (string& s, det.headings)
				str::trim(s) ;

			pt::ptree& curTree = indexLots ? indexTree : nonIndexTree ;

			curTree.put ((format ("%1%.%2%") % det.headings[1] % headings[1]).str(), det.lots[0]) ;
			curTree.put ((format ("%1%.%2%") % det.headings[1] % headings[2]).str(), det.lots[1]) ;
			curTree.put ((format ("%1%.%2%") % det.headings[1] % headings[3]).str(), det.lots[2]) ;
		}
	}

	pt::write_xml (cout, tree, pt::xml_writer_settings<char>(' ', 4)) ;
	fin.close() ;
}
