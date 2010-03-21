#include "std.hxx"
#include "boost-xpressive.hxx"
#include "boost-spirit.hxx"
#include "file-reading.hxx"

#include <boost/assign/std/set.hpp>
#include <boost/assign/std/vector.hpp>
#include <boost/assign/list_inserter.hpp>
#include <boost/iterator/zip_iterator.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
using namespace boost::assign ;

typedef vector<string> StringVector ;
typedef vector<double> DoubleVector ;

struct ScripDetails
{
	StringVector titles ;
	DoubleVector prices ;
} ;


	BOOST_FUSION_ADAPT_STRUCT(
		ScripDetails,
		(StringVector, titles)
		(DoubleVector, prices)
		)

int main (int argc, char** argv)
{
	parse_args (argc, argv) ;
	fs::fstream fin ;
	fin.open (inputFile, ios_base::in | ios_base::binary) ;

	string l ;
	pt::ptree tree ;
	xpr::smatch results ;

	qi::rule<string::iterator, string(), ascii::space_type> stringWithQuotes
		= qi::lexeme['"' >> +(qi::char_ - '"') >> '"'] ;

	qi::rule<string::iterator, DoubleVector(), ascii::space_type> quotedDoubles =
		(qi::lit('"') >> qi::double_ >> '"') % ',' ;

	qi::rule<string::iterator, ScripDetails(), ascii::space_type> stringsAndDoubles =
		qi::repeat(3)[stringWithQuotes >> ','] >> quotedDoubles ;

	vector<int> requiredIndices ;
	requiredIndices += 4, 5, 6, 8 ;

	StringVector headings ;
	while (getline (fin, l, '\n'))
	{
		IGNORE_BLANK_LINE(l) ;
		string::iterator iterBegin = l.begin() ;
		string::iterator iterEnd = l.end() ;
		ScripDetails scripDetails ;

		if (qi::phrase_parse(iterBegin, iterEnd, stringsAndDoubles, ascii::space, scripDetails))
		{
			string date (scripDetails.titles[2]) ;
			pt::ptree& curTree = tree.put_child ((format("Nse Historical Data.%1%") % date).str(), pt::ptree()) ;

			BOOST_FOREACH (int i, requiredIndices)
				curTree.put (headings[i], scripDetails.prices[i]) ;
		}
		else if (!qi::phrase_parse (iterBegin, iterEnd, stringWithQuotes % ',', ascii::space, headings))
		{
			// throw error ;
		}
	}

	pt::write_xml (cout, tree, pt::xml_writer_settings<char>(' ', 4)) ;
	fin.close() ;
}
