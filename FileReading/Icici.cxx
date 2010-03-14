#include "std.hxx"
#include "file-reading.hxx"
#include "boost-xpressive.hxx"

#include <boost/assign/std/set.hpp>
#include <boost/assign/list_inserter.hpp>
using namespace boost::assign ;

#include <boost/iterator/zip_iterator.hpp>

void fillValues (const boost::tuple<const string&, const double&>& p_tuple,
		pt::ptree& p_tree)
{
	p_tree.put (camelCase(p_tuple.get<0>()), p_tuple.get<1>()) ;
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

int main (int argc, char** argv)
{
	parse_args (argc, argv) ;
	fs::fstream fin ;
	fin.open (inputFile, ios_base::in | ios_base::binary) ;

	pt::ptree tree ;

	set<string> ignoreFields ;

	insert (ignoreFields)
		("DATE") ("LAST TRADED TIME") ("DAY VOLUME")
		("% CHANGE") ("BEST OFFER PRICE") ("BEST BID PRICE") ("BEST OFFER QTY")
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

	vector<double> nseValues, bseValues ;
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
			if (!ignoreFields.count(field))
			{
				fields.push_back (field) ;
				string dummy ;
				line = getTDline (fin, dummy) ;
				if (xpr::regex_match (line, results, tableContent))
				{
					string val (results[contentTag]);
					str::erase_all (val, ",") ;
					nseValues.push_back (lexical_cast<double>(val)) ;
				}

				line = getTDline (fin, dummy) ;
				if (xpr::regex_match (line, results, tableContent))
				{
					string val (results[contentTag]);
					str::erase_all (val, ",") ;
					bseValues.push_back (lexical_cast<double>(val)) ;
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
