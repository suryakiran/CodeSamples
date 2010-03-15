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

	xpr::smatch results ;
	string l ;

	pt::ptree tree ;
	pt::ptree& codesTree = tree.put_child ("Icici Search.Codes", pt::ptree()) ;

	xpr::mark_tag codeTag(1) ;

	xpr::sregex headReg = 
		beginTd >> textBeforeCloseAnchor >> closeAnchor
		>> (codeTag= textBeforeAnchor) >> endTd ;

	xpr::sregex codeReg = 
		beginTd >> textBeforeCloseAnchor >> closeAnchor >> skipAnchor
		>> (codeTag= textBeforeAnchor) >> skipAnchor >> endTd ;

	while (getline (fin, l, '\n'))
	{
		IGNORE_BLANK_LINE(l) ;

		if (xpr::regex_match (l, results, headReg))
		{
			string dummy(""), head (results[codeTag]) ;
			if (head == "NSE Code" || head == "BSE Code")
			{
				while (getline(fin, l, '\n'))
				{
					IGNORE_BLANK_LINE(l) ;
					if (xpr::regex_match (l, results, codeReg))
					{
						string code (results[codeTag]) ;
						str::erase_last (code, "EQ") ;
						codesTree.put(head, code) ;
						break ;
					}
				}
			}

			if (codesTree.find("BSE Code") != codesTree.not_found())
				break ;
		}
	}

	pt::write_xml (cout, tree, pt::xml_writer_settings<char>(' ', 4)) ;
	fin.close() ;
}
