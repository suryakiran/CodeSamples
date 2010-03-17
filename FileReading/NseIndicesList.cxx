#include "std.hxx"
#include "boost-xpressive.hxx"
#include "file-reading.hxx"

#include <boost/assign/std/set.hpp>
#include <boost/assign/std/vector.hpp>
#include <boost/assign/list_inserter.hpp>
#include <boost/iterator/zip_iterator.hpp>
using namespace boost::assign ;

void fillIndexDetails (const boost::tuple<int, const string&, const string&>& p_tuple,
					   pt::ptree& p_tree)
{
	string num ((format ("Index %1%") % p_tuple.get<0>()).str()) ;
	pt::ptree& curTree = p_tree.put_child (num, pt::ptree()) ;
	curTree.put ("Value", p_tuple.get<1>()) ;
	curTree.put ("Display", p_tuple.get<2>()) ;
}

int main (int argc, char** argv)
{
	parse_args (argc, argv) ;
	fs::fstream fin ;
	fin.open (inputFile, ios_base::in | ios_base::binary) ;

	string l ;
	pt::ptree tree ;
	xpr::smatch results ;

	xpr::mark_tag valueTag(1), displayTag(2) ;

	pt::ptree& indicesTree = tree.put_child ("Nse Indices", pt::ptree()) ;
	xpr::sregex optionReg =
		xpr::as_xpr ('<') >> "option" >> +_s >> "value" >> *_s >> '=' >> *_s
		>> (valueTag= quotedWord) >> *(~(xset= '>')) >> '>' 
		>> (displayTag= textBeforeAnchor) >> *_s 
		>> '<' >> *_s >> "/option" >> *_s >> '>'
		;

	vector<string> indexNames, indexDisplayNames ;
	vector<int> indexNumbers ;

	int num(0) ;
	while (getline (fin, l, '\n'))
	{
		IGNORE_BLANK_LINE(l) ;
		if (xpr::regex_match (l, results, optionReg))
		{
			string val (results[valueTag]) ;
			str::erase_all (val, "\"") ;

			indexNames += val ;
			indexDisplayNames += results[displayTag] ;
			indexNumbers += (++num) ;
		}
	}

#define BEGIN_TUPLE(vec1,vec2,vec3)\
	boost::make_tuple(vec1.begin(),vec2.begin(),vec3.begin())

#define END_TUPLE(vec1,vec2,vec3)\
	boost::make_tuple(vec1.end(),vec2.end(),vec3.end())

	std::for_each (
			boost::make_zip_iterator (
				BEGIN_TUPLE (indexNumbers, indexNames, indexDisplayNames)
				),
			boost::make_zip_iterator (
				END_TUPLE (indexNumbers, indexNames, indexDisplayNames)
				),
			phx::bind(fillIndexDetails, pha::arg1, phx::ref(indicesTree))
			) ;

	pt::write_xml (cout, tree, pt::xml_writer_settings<char>(' ', 4)) ;
	fin.close() ;
}
