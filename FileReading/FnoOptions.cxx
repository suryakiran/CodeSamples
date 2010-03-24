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
//	xpr::smatch results ;

	vector<string> results ;

	while (getline (fin, l, '\n'))
	{
		IGNORE_BLANK_LINE(l) ;
		if (str::icontains (l, "price information"))
		{
			vector <string> vs ;
			str::split (vs, l, boost::is_any_of ("<>"), boost::token_compress_on) ;
			BOOST_FOREACH (string s, vs)
			{
				str::trim (s) ;
				if (
						s.empty() || 
						str::iequals   (s, "th") ||
						str::iequals   (s, "b") ||
						str::iequals   (s, "/b") ||
						str::iequals   (s, "tr") ||
						str::iequals   (s, "/table") ||
						str::iequals   (s, "/tbody") ||
						str::iequals   (s, "tbody") ||
						str::icontains (s, "th class") ||
						str::icontains (s, "price information") ||
						str::icontains (s, "td class") ||
						str::icontains (s, "table border") ||
						str::icontains (s, "table align") ||
						str::icontains (s, "/td") ||
						str::icontains (s, "/th") ||
						str::icontains (s, "/tr")
				   )
					continue ;
				results.push_back (s) ;
			}
			break ;
		}
	}

	printContainer ("Results", results) ;

	pt::write_xml (cout, tree, pt::xml_writer_settings<char>(' ', 4)) ;
	fin.close() ;
}
