#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <sstream>

#include <boost/regex.hpp>
#include <boost/program_options.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/foreach.hpp>
#include <boost/spirit.hpp>

#include <ng-details.hpp>

using namespace boost::algorithm ;
using namespace boost::spirit ;
using namespace std ;
using namespace boost ;

namespace po  = boost::program_options ;

string inputFile, outputFile ;

NgImageDetails ngImageDetails ;

void parse_args (int argc, char **argv)
{
	po::options_description desc ("Allowed Options") ;
	desc.add_options()
		("input-file",      po::value <string>(), "Path to html file")
		("output-file",     po::value <string>(), "Path to serialized xml file")
		;

	po::variables_map vm ;
	po::store (po::parse_command_line (argc, argv, desc), vm) ;
	po::notify (vm) ;

	if (vm.count ("input-file"))
		inputFile=vm["input-file"].as<string>() ;

	if (vm.count ("output-file"))
		outputFile=vm["output-file"].as<string>() ;
}

void save_ng_details (void)
{
	ofstream ofs (outputFile.c_str()) ;
	assert (ofs.good()) ;
	boost::archive::xml_oarchive oa (ofs) ;
	oa << BOOST_SERIALIZATION_NVP (ngImageDetails) ;
}

void get_image_title (const string& s)
{
	string ls (s) ;
	ierase_all (ls, "<h3>") ; 
	ierase_all (ls, "</h3>") ; 

	ngImageDetails.m_title = ls ;
}

void get_image_description (const string& s)
{
	string desc (s) ;
	ierase_all (desc, "</p>") ;
	ierase_all (desc, "<p>") ;

	regex reg ("<[^>]*>") ;
	erase_all_regex (desc, reg) ;

	ngImageDetails.m_description = desc ;
}

int main (int argc, char **argv)
{
	parse_args (argc, argv) ;

	if (inputFile.empty()) return -1 ;

	string l ;
	vector<string> vs ;
	string image ;

	bool imageDetailsBegins (false) ;

	fstream fin ;
	fin.open (inputFile.c_str(), ios_base::in | ios_base::binary) ;
	while (getline (fin, l, '\n'))
	{
		trim (l) ;
		if (l.empty()) continue ;

		if (iequals(l, "<div class=\"summary\">"))
			imageDetailsBegins = true ;


		if (
				icontains (l, "buy a print of this photo") || 
				icontains (l, "a class=\"previous\"")
		   )
		{
			imageDetailsBegins = false ;
		}

		if (imageDetailsBegins && istarts_with (l, "<h3>"))
			get_image_title (l) ;

		if (imageDetailsBegins && icontains (l, "class=\"description\""))
			get_image_description (l) ;

		if (contains (l, "enlarge") && contains (l, "src="))
		{
			split (vs, l, is_any_of ("<>"), token_compress_on) ;
			BOOST_FOREACH (string s, vs)
			{
				if (icontains (s, "img alt="))
				{
					replace_all (s, "\"", "") ;
					split (vs, s, is_any_of ("=/"), token_compress_on) ;
					image = vs[vs.size() -1];
					replace_all (image, "-ga", "-xl") ;
					break ;
				}
			}
		}
	}

	ostringstream os ;

	os << "http://photography.nationalgeographic.com/staticfiles/NGS/Shared/StaticFiles" 
	   << "/Photography/s/POD/" << image[0] << '/' << image ;
	ngImageDetails.m_primaryName = os.str() ;

	os.str("") ;
	os << "http://photography.nationalgeographic.com/staticfiles/NGS/Shared/StaticFiles" 
	   << "/Photography/s/POD/" << image ;
	ngImageDetails.m_secondaryName = os.str() ;

	fin.close() ;

	save_ng_details () ;

	return 0 ;
}
