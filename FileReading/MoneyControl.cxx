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

	set<string> validFields ;
	insert (validFields) 
		("Open") ("High") ("Low") ("52 Wk") ("Last Traded Price") 
		("Prev Close") ("Year High") ("Year Low") ;

	typedef pair<bool, bool> BoolPair ;
	map<string, BoolPair> fieldCaptured ;

	BOOST_FOREACH (const string& s, validFields)
		fieldCaptured[s] = make_pair(false, false) ; //First bse, second nse ;

	fieldCaptured.erase("52 Wk") ;

	xpr::smatch results ;
	string l ;

	xpr::mark_tag textTag(1), priceTag(1) ;
	pt::ptree tree ;
	pt::ptree& nsePrices = tree.put_child ("Scrip.PriceDetails.Nse", pt::ptree()) ;
	pt::ptree& bsePrices = tree.put_child ("Scrip.PriceDetails.Bse", pt::ptree()) ;

	nsePrices.put ("Last Traded Price", 0.0) ;
	bsePrices.put ("Last Traded Price", 0.0) ;

	xpr::sregex overview =
		as_xpr("<b>") >> *_s >> "Overview" >> *_s >> "</b>" ;

	xpr::sregex validText =
		as_xpr(*(~(xset= '<','&',';'))) ;

	xpr::sregex spanReg = 
		as_xpr('<') >> *_s >> "span" >> *_s >> "class" >> *_s >> '=' >> *_s
		>> quotedWord >> *_s >> '>' >> (priceTag= textBeforeAnchor) >> "</span>" ;

	xpr::sregex strongDetails =
		as_xpr("\"det\"") >> *_s >> '>' >> *_s >> '<' >> *_s >> "strong" >> *_s ;

	xpr::sregex fieldTag =
		as_xpr("\"hed\"") | strongDetails ;

	xpr::sregex td =
		as_xpr("<td class") >> *_s >> "=" >> *_s >> fieldTag >> '>'
		>> *_s >> (textTag= validText) ;

	xpr::sregex price =
		as_xpr("<td") >> *(~(xset= '>')) >> '>' >> *_s
		>> (priceTag = *(_d|numberDelims)) >> *_s >> '<' ;

	bool priceDetailsBegin (false) ;
	bool bseDetails (true) ;
	string prevField ("") ;

	while (getline (fin, l, '\n'))
	{
		IGNORE_BLANK_LINE(l) ;

		if (xpr::regex_search (l, results, overview))
			priceDetailsBegin = true ;

		if (!priceDetailsBegin)
			continue ;

		if (xpr::regex_search (l, results, spanReg))
		{
			string field ("Last Traded Price") ;
			string s (results[priceTag]) ;
			str::trim(s) ;
			str::erase_all (s, ",") ;
			double price (0.0) ;
			try { price = lexical_cast<double>(s) ; }
			catch (...) { }
			if (!fieldCaptured[field].first)
			{
				bsePrices.put(field, price) ;
				fieldCaptured[field].first = true ;
			}
			else if (!fieldCaptured[field].second)
			{
				nsePrices.put(field, price) ;
				fieldCaptured[field].second = true ;
			}
		}

		if (xpr::regex_search (l, results, td))
		{
			string field (results[textTag]) ;
			str::trim(field) ;
			str::erase_all(field, ".") ;
			if (validFields.count(field))
			{
				string currentField (field) ;
				if (prevField == "High")
					currentField = "Year High" ;
				if (prevField == "Low")
					currentField = "Year Low" ;

				prevField = field ;
				while (getline (fin, l, '\n'))
				{
					IGNORE_BLANK_LINE(l) ;
					if (regex_search (l, results, price))
					{
						string s (results[priceTag]) ;
						str::erase_all (s, ",") ;

						double price (0.0) ;
						try { price = lexical_cast<double>(s); }
						catch (...) { }

						if (!fieldCaptured[currentField].first)
						{
							bsePrices.put(currentField, price) ;
							fieldCaptured[currentField].first = true ;
						}
						else if (!fieldCaptured[currentField].second)
						{
							nsePrices.put(currentField, price) ;
							fieldCaptured[currentField].second = true ;
						}

						break ;
					}
				}
			}
		}
	}

	pt::write_xml (cout, tree, pt::xml_writer_settings<char>(' ', 4)) ;
	fin.close() ;
}
