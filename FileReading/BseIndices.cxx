#include "std.hxx"
#include "boost-xpressive.hxx"
#include "file-reading.hxx"

#include <boost/assign/std/vector.hpp>
#include <boost/assign/list_inserter.hpp>
using namespace boost::assign ;


int main (int argc, char** argv)
{
	parse_args (argc, argv) ;
	fs::fstream fin ;
	fin.open (inputFile, ios_base::in | ios_base::binary) ;

	xpr::smatch results ;
	xpr::mark_tag indexTag(1), numTag(1) ;
	string l ;

	vector<string> priceFields ;
	priceFields += "Open", "High", "Low", "Last", "Prev Close", "Change", "Pc Change" ;

	pt::ptree tree ;
	pt::ptree& indexTree = tree.put_child ("Indices.Bse", pt::ptree()) ;

	xpr::sregex indexLink =
		beginTag("a") >> *_s >> beginTag("FONT")
		>> *_s >> (indexTag= textBeforeAnchor)
		>> endTag("font", false) >> *_s >> endTag("a")
		;

	xpr::sregex tdReg =
		beginTag("TD") >> *_s >> beginTag("FONT")
		>> *_s >> (numTag= floatNumber) >> *_s 
		>> endTag("font", false) >> *_s >> endTag("TD", false)
		;

	xpr::sregex trBegin = beginTag("TR", true, false) ;
	xpr::sregex trEnd = endTag("TR", true);

	while (getline (fin, l, '\n'))
	{
		IGNORE_BLANK_LINE(l) ;
		str::erase_all(l, ",");

		if (xpr::regex_search (l, results, indexLink))
		{
			pt::ptree& curTree = indexTree.put_child(string(results[indexTag]), pt::ptree());
			int i(0);
			while(getline (fin, l, '\n'))
			{
				IGNORE_BLANK_LINE(l) ;
				str::erase_all(l, ",");

				if (xpr::regex_search (l, results, tdReg))
					curTree.put(priceFields[i++], lexical_cast<double>(results[numTag]));

				if (xpr::regex_search (l, results, trEnd))
					break;
			}
		}
	}

	pt::write_xml (cout, tree, pt::xml_writer_settings<char>(' ', 4)) ;
	fin.close() ;
}
