
#include <std.hxx>
#include <boost-spirit.hxx>
#include <boost-xpressive.hxx>

#include <boost/program_options.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

#include "ng-details.hpp"

namespace str = boost::algorithm ;
namespace po  = boost::program_options ;

using namespace boost::gregorian ;

string inputFile, outputFile ;

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

bool trimLine (string& p_line)
{
	str::trim(p_line);
	return (!p_line.empty()) ;
}

int main (int argc, char **argv)
{
	parse_args (argc, argv) ;

	if (inputFile.empty()) return -1 ;

	string l ;

	xpr::smatch results ;
	xpr::mark_tag titleTag(1), descTag(1);
	NgImageDetails ngDetails;

	fstream fin ;
	fin.open (inputFile.c_str(), ios_base::in | ios_base::binary) ;

	string divDownloadLink ("^<\\s*div\\s+class\\s*=\\s*(['\"])download_link\\1\\s*>") ;
	xpr::sregex aHrefTag = xpr::sregex::compile ("<\\s*a\\s+href\\s*=\\s*(['\"])([^\\1]*)\\1\\s*>");
	xpr::sregex downloadLink =
		xpr::sregex::compile (divDownloadLink) >> *_s >> aHrefTag
		;
	xpr::sregex title =
		beginTag("h2", true, false) >> (titleTag= xpr::sregex::compile("[^<]*")) >> endTag("h2");

	xpr::sregex desc =
		beginTag("p", true, false) >> (descTag= xpr::sregex::compile("[^<]*")) >> endTag("p");

	bool detailsOver(false);
	while (getline (fin, l, '\n'))
	{
		if (!trimLine(l))
			continue;
		if (xpr::regex_search (l, results, downloadLink))
		{
			BOOST_FOREACH(const xpr::smatch& res, results.nested_results())
			{
				if (res.regex_id() == aHrefTag.regex_id())
				{
					ngDetails.setValue("ImageName", string(res[2]));
					break;
				}
			}

			while (getline(fin, l, '\n'))
			{
				if (!trimLine(l))
					continue ;

				if (xpr::regex_match (l, results, title))
				{
					ngDetails.setValue("Title", string(results[titleTag]));
					continue ;
				}

				if (xpr::regex_match(l, results, desc))
				{
					ngDetails.setValue("Description", string(results[descTag]));
					detailsOver = true; ;
					break ;
				}
			}

			if (detailsOver)
				break;
		}
	}
	fin.close() ;

	ngDetails.printTree(outputFile);
	return 0 ;
}
