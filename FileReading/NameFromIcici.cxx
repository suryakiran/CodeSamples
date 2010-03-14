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
	pt::ptree& nameTree = tree.put_child ("Search From Icici", pt::ptree()) ;

	xpr::smatch results ;
	xpr::mark_tag codeTag(1) ;

	xpr::sregex checkBox =
		as_xpr("<td") >> *_s >> "class" >> *_s >> "=" >> *_s >> "\"content\"" >> *_s >> '>'
		>> *_s >> "<input type=\"checkbox\"" ;

	xpr::sregex itemReg =
		as_xpr("<td") >> *_s >> "class" >> *_s >> "=" >> *_s >> "\"content\"" >> *_s >> '>'
		>> (codeTag= textBeforeAnchor) >> "</td>";


	while (getline (fin, l, '\n'))
	{
		IGNORE_BLANK_LINE(l) ;

		if (xpr::regex_search (l, results, checkBox))
		{
			bool codeLine (true) ;
			string code ;
			while (getline (fin, l, '\n'))
			{
				IGNORE_BLANK_LINE(l) ;
				if (regex_match(l, results, itemReg))
				{
					if (codeLine)
					{
						code = results[codeTag] ;
						codeLine = false ;
						continue ;
					}
					else 
					{
						nameTree.put (code, results[codeTag]) ;
						break ;
					}
				}
			}
		}
	}

	pt::write_xml (cout, tree, pt::xml_writer_settings<char>(' ', 4)) ;
	fin.close() ;
}
