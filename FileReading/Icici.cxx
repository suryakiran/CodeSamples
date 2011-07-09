#include "std.hxx"
#include "file-reading.hxx"
#include "boost-xpressive.hxx"

#include <boost/assign/std/set.hpp>
#include <boost/assign/list_inserter.hpp>
using namespace boost::assign ;

#include "stock-prices.hxx"

int main (int argc, char** argv)
{
	parse_args (argc, argv) ;
	fs::fstream fin ;
	fin.open (inputFile, ios_base::in | ios_base::binary) ;

	pt::ptree tree ;

	set<string> requiredFields ;
	map<string, StringFieldPair> fieldMap;
	
	insert (requiredFields)
		("LAST TRADE PRICE") ("DAY HIGH") ("DAY LOW") ("52 WEEK HIGH") ("52 WEEK LOW")
		("DAY OPEN") ("PREVIOUS DAY CLOSE")
		;

	insert (fieldMap)
		("LAST TRADE PRICE", FIELD_ID(CurrentPrice)) ("PREVIOUS DAY CLOSE", FIELD_ID(PreviousDayClose))
		("DAY HIGH", FIELD_ID(DayHigh)) ("DAY LOW", FIELD_ID(DayLow)) ("DAY OPEN", FIELD_ID(DayOpen))
		("52 WEEK HIGH", FIELD_ID(YearLow)) ("52 WEEK LOW", FIELD_ID(YearHigh))
		;

    string l ;

	tree.put("Scrip.Details.Source", "Icici") ;
	pt::ptree& nsePrices = tree.put_child ("Scrip.Prices.Nse", pt::ptree()) ;
	pt::ptree& bsePrices = tree.put_child ("Scrip.Prices.Bse", pt::ptree()) ;

	xpr::mark_tag headingTag(1), contentTag(1) ;
	xpr::smatch results ;
	xpr::sregex tableHeading =
		as_xpr("<td") >> *_s >> "align" >> *_s >> "=" >> *_s 
		>> quotedWord >> *_s
		>> "class" >> *_s >> "=" >> *_s
		>> "\"tbl_dataBOLD\"" >> *_s >> '>'
		>> (headingTag= *(~(xset='<'))) >> "</td>"
		;

	xpr::sregex tableContent =
		as_xpr("<td") >> *_s >> "align" >> *_s >> "=" >> *_s 
		>> quotedWord >> *_s
		>> "class" >> *_s >> "=" >> *_s
		>> "\"content\"" >> *_s >> '>'
		>> (contentTag= *(_d | numberDelims)) >> "</td>"
		;

	vector<double> nseValues(requiredFields.size(), 0.0);
	vector<double> bseValues(requiredFields.size(), 0.0) ;

	vector<string> fields ;

	while (getline (fin, l, '\n'))
	{
		IGNORE_BLANK_LINE(l) ;

		string line(getTDline (fin, l)) ;

		if (line.empty())
			continue ;

		if (xpr::regex_match (line, results, tableHeading))
		{
			string field (results[headingTag]) ;
			if (requiredFields.count(field))
			{
				fields.push_back (fieldMap[field].first) ;
				int idx (fieldMap[field].second);
				string dummy ;
				line = getTDline (fin, dummy) ;
				if (xpr::regex_match (line, results, tableContent))
				{
					string val (results[contentTag]);
					str::erase_all (val, ",") ;
					nseValues[idx] = lexical_cast<double>(val) ;
				}

				line = getTDline (fin, dummy) ;
				if (xpr::regex_match (line, results, tableContent))
				{
					string val (results[contentTag]);
					str::erase_all (val, ",") ;
					bseValues[idx] = lexical_cast<double>(val) ;
				}
			}
		}

		line.clear() ;
	}

    fin.close() ;

	std::for_each (
		boost::make_zip_iterator (boost::make_tuple(fields.begin(), nseValues.begin())),
		boost::make_zip_iterator (boost::make_tuple(fields.end(), nseValues.end())),
		phx::bind (fillValues, pha::arg1, phx::ref(nsePrices))
		) ;

	std::for_each (
		boost::make_zip_iterator (boost::make_tuple(fields.begin(), bseValues.begin())),
		boost::make_zip_iterator (boost::make_tuple(fields.end(), bseValues.end())),
		phx::bind (fillValues, pha::arg1, phx::ref(bsePrices))
		) ;

	pt::write_xml (cout, tree, pt::xml_writer_settings<char>(' ', 4)) ;

	return 0 ;
}
