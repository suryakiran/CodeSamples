#include<boost/filesystem/path.hpp>
#include <boost/program_options.hpp>
#include <boost/spirit.hpp>

#include <boost/algorithm/string.hpp>

#include <fstream>
#include <string>
#include <iostream>

using namespace boost::filesystem ;
using namespace boost::algorithm ;
using namespace boost::spirit ;
using namespace std ;
namespace po  = boost::program_options ;

void parse_args (int argc, char** argv)
{
	po::options_description desc ("Allowed Options") ;
	desc.add_options()
		("help",           "Show this message")
		("html-file",      po::value <string>(), "Path to html file")
		;

	po::variables_map vm ;
	try
	{
		po::store (po::parse_command_line (argc, argv, desc), vm) ;
		po::notify (vm) ;
	}
	catch( std::exception& e)
	{
		cout << "Exception in reading command line variables: " << e.what() << endl ;
	}

	if (vm.count ("html-file"))
	{
		inputFile = vm["html-file"].as<string>() ;
	}
}

string get_image_title (const string& s)
{
	string ls (s) ;
	cout << s << endl ;
	ierase_all (ls, "<h3>") ; 
	ierase_all (ls, "</h3>") ; 

	cout << ls << endl ;
	return ls ;
}

int main (int argc, char** argv)
{
	parse_args (argc, argv) ;


	if (!inputFile.empty()) 
	{
		fstream fin ;
		fin.open (inputFile.c_str(), ios_base::in | ios_base::binary) ;

		string l;
		bool begins (false) ;

		while (getline (fin, l, '\n')) 
		{
			trim (l) ;

			if (l.empty())
				continue ;

			if (iequals(l, "<div class=\"summary\">"))
				begins = true ;

			if (
					icontains (l, "buy a print of this photo") || 
					icontains (l, "a class=\"previous\"")
			   )
			{
				begins = false ;
			}

			if (!begins)
				continue ;

			if (istarts_with (l, "<h3>"))
				get_image_title (l) ;

		}
	}

	cin.get() ;
	return 0 ;
}
