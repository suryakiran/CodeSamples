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
	pt::ptree& codeSearch = tree.put_child ("Search From Icici Code", pt::ptree()) ;

	xpr::smatch results ;
	xpr::mark_tag nseCodeTag(1), bseCodeTag(1) ;

	xpr::sregex nseCode =
		as_xpr("<td") >> *(~(xset= '>')) >> '>' >> *_s >> "<b>"
		>> (nseCodeTag= *(~(xset= '<')));

	xpr::sregex bseCode =
		as_xpr("<td") >> *(~(xset= '>')) >> '>' >> *_s >> "<b>"
		>> (bseCodeTag= +(_d));

	while (getline (fin, l, '\n'))
	{
		IGNORE_BLANK_LINE(l) ;
		if (str::contains (l, "NSE Code"))
		{
			while(getline(fin, l, '\n'))
			{
				IGNORE_BLANK_LINE(l) ;
				if (xpr::regex_search(l, results, nseCode))
				{
					string s (results[nseCodeTag]) ;
					str::erase_last (s, "EQ") ;
					codeSearch.put ("Nse Code", s) ;
					break ;
				}
			}
		}

		if (str::contains (l, "BSE Code"))
		{
			while(getline(fin, l, '\n'))
			{
				IGNORE_BLANK_LINE(l) ;
				if (xpr::regex_search(l, results, bseCode))
				{
					codeSearch.put ("Bse Code", results[bseCodeTag]) ;
					break ;
				}
			}
		}

		if (codeSearch.find("Bse Code") != codeSearch.not_found())
			break ;
	}

	pt::write_xml (cout, tree, pt::xml_writer_settings<char>(' ', 4)) ;
	fin.close() ;
}
