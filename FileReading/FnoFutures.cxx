#include "std.hxx"
#include "boost-xpressive.hxx"
#include "file-reading.hxx"

int main (int argc, char** argv)
{
	parse_args (argc, argv) ;
	fs::fstream fin ;
	fin.open (inputFile, ios_base::in | ios_base::binary) ;
	string l ;
	pt::ptree tree ;
	xpr::smatch results ;

	xpr::mark_tag priceTag(1), valueTag(2);

	xpr::sregex priceDetails =
		beginTr >> *_s 
		>> beginTh 	>> *_s >> !boldBegin >> *_s >> (priceTag= textBeforeAnchor) 
		>> *_s >> !boldEnd >> *_s >> endTh
		>> *_s >> beginTd >> textBeforeCloseAnchor >> '>' >> *_s 
		>> !boldBegin >> *_s >> (valueTag= floatNumber) >> *_s >> !boldEnd >> *_s >> endTd
		>> *_s >> endTr
		;

	pt::ptree& futuresTree = tree.put_child ("Futures Details", pt::ptree()) ;
	while (getline (fin, l, '\n'))
	{
		IGNORE_BLANK_LINE(l) ;
		if (xpr::regex_search(l, results, priceDetails))
		{
			xpr::sregex_iterator regIter (l.begin(), l.end(), priceDetails);
			xpr::sregex_iterator regIterEnd;
			for(; regIter != regIterEnd; ++regIter) 
			{
				results = *regIter ;
				string priceType (results[priceTag]);
				string value (results[valueTag]);

				str::erase_all(priceType, ".");

				if (str::contains(value, "."))
					futuresTree.put(priceType, lexical_cast<double>(value));
				else
					futuresTree.put(priceType, lexical_cast<size_t>(value));
			}
		}
	}

//	printContainer ("Results", results) ;

	pt::write_xml (cout, tree, pt::xml_writer_settings<char>(' ', 4)) ;
	fin.close() ;
}
