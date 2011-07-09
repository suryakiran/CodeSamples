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

	vector<string> priceFields ;
	priceFields += "Prev Close", "Open", "High", "Low", "Last", "Change" ;

	pt::ptree tree ;
	xpr::smatch results ;
	string l ;

	xpr::mark_tag valueTag(1), nameTag(1) ;

	xpr::sregex indexReg = 
		tdAnchor >> aHref >> "/content/indices" >> textBeforeCloseAnchor >> '>'
		>> *_s >> (nameTag= textBeforeAnchor) >> endA >> *_s >> endTd ;

	xpr::sregex valueReg =
		tdAnchor >> (valueTag= +(_d | numberDelims)) >> *_s >> endTd ;

	while (getline (fin, l, '\n'))
	{
		IGNORE_BLANK_LINE(l) ;
		if (xpr::regex_match (l, results, indexReg))
		{
			string childName ("Nse Indices.") ;
			childName += results[nameTag] ;
			pt::ptree& indexTree = tree.put_child (childName, pt::ptree()) ;

			size_t lineNum(0) ;
			while(getline(fin, l, '\n'))
			{
				IGNORE_BLANK_LINE(l) ;
				if (xpr::regex_match (l, results, valueReg))
				{
					double price(0.0) ;
					try { price = lexical_cast<double>(results[valueTag]) ; }
					catch (...) { }
					indexTree.put (priceFields[lineNum], price) ;
					if (++lineNum == priceFields.size())
						break ;
				}
				else
					continue ;
			}
		}

	}

	pt::write_xml (cout, tree, pt::xml_writer_settings<char>(' ', 4)) ;
	fin.close() ;
}
