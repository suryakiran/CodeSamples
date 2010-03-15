#ifndef FILE_READING_HXX
#define FILE_READING_HXX 1

#include <boost/program_options.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/filesystem/exception.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
namespace pt = boost::property_tree ;

#include <boost/lexical_cast.hpp>
using boost::lexical_cast ;

#include <boost/spirit/include/phoenix.hpp>

namespace phx = boost::phoenix ;
namespace pha = phx::arg_names ;
namespace po = boost::program_options ;
namespace fs = boost::filesystem ;

#define IGNORE_BLANK_LINE(l)\
	boost::algorithm::trim(l) ;\
	if (l.empty()) continue 

#endif

fs::path inputFile ;

template <class T>
T toType (const string& p_input)
{
	T output (str::erase_all_copy (p_input, "\"")) ;
	return output ;
}

string camelCase (const string& p_input)
{
	string resultString (p_input) ;

	str::to_lower(resultString) ;
	resultString = str::replace_all_copy (resultString, "_", " ") ;
	resultString = str::replace_all_copy (resultString, "  ", " ") ;

	str::replace_all_regex (resultString, boost::regex("([-/()])(.)"),
			string("\\1\\U\\2")) ;

	str::replace_all_regex (resultString, boost::regex(" (.)"),
			string(" \\U\\1")) ;

	resultString[0] = toupper(resultString[0]) ;

	return resultString ;
}

void parse_args(int argc, char **argv)
{
	po::options_description desc ("Allowed Options") ;
	desc.add_options()
		("help",           "Show this message")
		("file",  po::value <string>(), "Input File")
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

	if (vm.count ("help"))
	{
		cout << desc << endl ;
		exit (-1);
	}

	if (vm.count ("file"))
	{
		inputFile = toType<fs::path>(vm["file"].as<string>()) ;
	}
}

string getTDline (std::istream& is, const string& currentLine)
{
	string l(currentLine), line ;

	if (l.empty())
	{
		while (getline (is, l, '\n'))
		{
			IGNORE_BLANK_LINE(l) ;
			if (!l.empty()) break ;
		}
	}

	if (str::starts_with (l, "<td align"))
	{
		line = l ;
		if (!str::ends_with (line, "</td>"))
		{
			while (getline (is, l, '\n'))
			{
				IGNORE_BLANK_LINE(l) ;
				line += ' ' + l ;
				if (str::ends_with(l, "</td>"))
					break ;
			}
		}
	}
	return line ;
}
