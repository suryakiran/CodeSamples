#include "std.hxx"
#include "boost-xpressive.hxx"
#include "file-reading.hxx"

#include <boost/assign/std/set.hpp>
#include <boost/assign/list_inserter.hpp>
using namespace boost::assign ;

void fillPrices (const xpr::smatch& p_match, const xpr::mark_tag& p_tag, vector<double>& p_prices)
{
	string s(p_match[p_tag]) ;
	str::erase_all(s, ",") ;
	double val (0.0) ;
	try { val = lexical_cast<double>(s) ; }
	catch (...) { }
	p_prices.push_back (val) ;
}

int main (int argc, char** argv)
{
	parse_args (argc, argv) ;
	fs::fstream fin ;
	fin.open (inputFile, ios_base::in | ios_base::binary) ;

	xpr::mark_tag numberTag(1), monthTag(2), dateTag(1);
	xpr::smatch results ;
	string l ;

	xpr::sregex numberDesc = 
		as_xpr(tdAnchor) >> (numberTag= number) >> *_s >> endTd >> *_s ;

	xpr::sregex dateReg =
		as_xpr(dateTag= xpr::repeat<1,2>(_d)) >> *_s >> (monthTag= longMonth) 
		>> *_s >> skipAnchor >> *_s >> endTd >> *_s 
		>> xpr::repeat<7,7>(numberDesc)
		;

	pt::ptree tree ;
	while (getline (fin, l, '\n'))
	{
		IGNORE_BLANK_LINE(l) ;
		str::erase_all (l, "&nbsp;") ;
		if (xpr::regex_search (l, results, dateReg))
		{
			xpr::sregex_iterator regIter(l.begin(), l.end(), dateReg) ;
			xpr::sregex_iterator regIterEnd ;
			for (; regIter != regIterEnd; ++regIter)
			{
				const xpr::smatch& results = *regIter ;
				string key = (format ("Bse Indices History.%1$02d-%2%") 
						% lexical_cast<int>(results[dateTag]) % results[monthTag]).str() ;

				pt::ptree& historyTree = tree.put_child (key, pt::ptree()) ;
				BOOST_FOREACH (const xpr::smatch& res, results.nested_results())
				{
					xpr::smatch::nested_results_type::const_iterator beg 
						(results.nested_results().begin()) ;
					xpr::smatch::nested_results_type::const_iterator end 
						(results.nested_results().end()) ;
					xpr::sregex_id_filter_predicate number_id (numberDesc.regex_id()) ;

					vector<double> prices ;
					std::for_each (
							boost::make_filter_iterator (number_id, beg, end),
							boost::make_filter_iterator (number_id, end, end),
							phx::bind(fillPrices, pha::arg1, numberTag, phx::ref(prices))
							) ;

					historyTree.put ("Open", prices[0]) ;
					historyTree.put ("High", prices[1]) ;
					historyTree.put ("Low", prices[2]) ;
					historyTree.put ("Close", prices[3]) ;
				}
			}
		}
	}

	pt::write_xml (cout, tree, pt::xml_writer_settings<char>(' ', 4)) ;
	fin.close() ;
}
