#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <sstream>

#include <boost/program_options.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/foreach.hpp>

#include "ng-details.hpp"

using namespace boost::algorithm ;
using namespace std ;

namespace po  = boost::program_options ;

string inputFile, reqdType ;

NgImageDetails ngImageDetails ;

void parse_args (int argc, char **argv)
{
	po::options_description desc ("Allowed Options") ;
	desc.add_options()
		("input-file",      po::value <string>(), "Path to serialized xml file")
		("description",     "Get Description of Image File")
		("title",           "Get Title of Image")
		("image-name",      "Get Image Name")
		;

	po::variables_map vm ;
	po::store (po::parse_command_line (argc, argv, desc), vm) ;
	po::notify (vm) ;

	if (vm.count ("input-file"))
		inputFile=vm["input-file"].as<string>() ;

	if (vm.count ("description"))
		reqdType = "Description" ;

	if (vm.count ("title"))
		reqdType = "Title" ;

	if (vm.count ("image-name"))
		reqdType = "ImageName" ;
}

void load_ng_details (void)
{
	try
	{
		ngImageDetails.loadTree(inputFile);
		ngImageDetails.printTree();
		string output ;
		output = ngImageDetails.getValue<string>(reqdType);
		cout << output ;
	}
	catch (std::exception& e)
	{
		cout << "Error:" << e.what() << endl ;
	}
}

int main (int argc, char **argv)
{
	try
	{
		parse_args (argc, argv) ;
	}
	catch (std::exception& e)
	{
		cout << "Exception from load-image-details: " << e.what() << endl ;
	}

	load_ng_details () ;
	return 0 ;
}
