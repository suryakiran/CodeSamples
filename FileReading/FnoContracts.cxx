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
	xpr::smatch results ;

	xpr::sregex callOrPut = xpr::as_xpr("CA")|"PA"|"CE"|"PE" ;

	xpr::sregex fnoDate =
		xpr::repeat<2,2>(_d) >> shortMonthU >> xpr::repeat<4,4>(_d) ;

	xpr::mark_tag siteTag(1), priceTag(1), dateTag(2), headingTag(1), typeTag(2) ;
	xpr::mark_tag strPriceTag (2) ;

	pt::ptree& futuresTree = tree.put_child ("Contracts.Futures", pt::ptree()) ;
	pt::ptree& optionsTree = tree.put_child ("Contracts.Options", pt::ptree()) ;

	xpr::sregex nodata=
		tdAnchor >> *_s >> '-' >> *_s >> endTd ;

	xpr::sregex price =
		tdAnchor >> *_s >> (priceTag= floatNumber) >> *_s >> endTd ;

	xpr::sregex tableHeading =
		as_xpr('<') >> *_s >> "th" >> +_s 
		>> *(~(xset= '>')) >> '>' 
		>> (headingTag= textBeforeAnchor) >> '<' >> *_s >> "/th" >> *_s >> '>'
		;

	xpr::sregex optstk =
		tdAnchor >> *_s >> aHref
		>> (siteTag= *(~(xset= '"'))) >> '"' >> *_s >> '>' >> *_s 
		>> "OPTSTK"|"OPTIDX" >> endA >> *_s >> endTd 
		;

	xpr::sregex futDate =
		tdAnchor >> *_s >> aHref
		>> (siteTag= *(~(xset= '?')) >> '?' >> "key=FUT" >> *(~(xset='"')) >> '"')
		>> *_s >> '>' >> *_s 
		>> (dateTag= fnoDate) >> *_s >> endA >> *_s >> endTd ;
		;

	xpr::sregex optDate =
		tdAnchor >> *_s >> aHref
		>> (siteTag= *(~(xset= '?')) >> '?' >> "key=OPT" >> *(~(xset='"')) >> '"') 
		>> *_s >> '>' >> *_s 
		>> (dateTag= fnoDate) >> *_s >> endA >> *_s >> endTd
		;

	xpr::sregex optType =
		tdAnchor >> *_s >> aHref
		>> (siteTag= *(~(xset= '?')) >> '?' >> "key=OPT" >> *(~(xset='"')) >> '"') 
		>> *_s >> '>' >> *_s 
		>> (typeTag= callOrPut) >> *_s >> endA >> *_s >> endTd
		;

	xpr::sregex optStrike =
		tdAnchor >> *_s >> aHref
		>> (siteTag= *(~(xset= '?')) >> '?' >> "key=OPT" >> *(~(xset='"')) >> '"') 
		>> *_s >> '>' >> *_s 
		>> (strPriceTag= floatNumber) >> *_s >> endA >> *_s >> endTd
		;

	vector<string> headings ;
	vector<int> requiredFuturesIndices, requiredOptionsIndices ;

	requiredFuturesIndices += 5,6,7,8,9 ;
	requiredOptionsIndices += 5,6,7,8 ;

	map<string, string> optionTypeMap ;
	optionTypeMap["CA"] = "CALL" ;
	optionTypeMap["CE"] = "CALL" ;
	optionTypeMap["PA"] = "PUT" ;
	optionTypeMap["PE"] = "PUT" ;

	while (getline (fin, l, '\n'))
	{
		IGNORE_BLANK_LINE(l) ;
		if (xpr::regex_match (l, results, tableHeading))
		{
			headings += results[headingTag] ;
			continue ;
		}

		if (xpr::regex_match (l, results, futDate))
		{
			pt::ptree& curTree = 
				futuresTree.put_child (string(results[dateTag]), pt::ptree()) ;
			curTree.put("Site", results[siteTag]) ;
			bool pricesBegin (false) ;
			vector<double> prices ;
			while (getline (fin, l, '\n'))
			{
				IGNORE_BLANK_LINE(l) ;
				if (xpr::regex_match (l, results, price))
				{
					prices += lexical_cast<double>(results[priceTag]) ;
					pricesBegin = true ;
					continue ;
				}
				else if (xpr::regex_match (l, results, nodata))
				{
					prices += -1.0 ;
					pricesBegin = true ;
					continue ;
				}
				else if (pricesBegin)
				{
					BOOST_FOREACH (int i, requiredFuturesIndices)
						curTree.put (headings[i], prices[i-3]) ;
					break ;
				}
			}
		}

		else if (xpr::regex_match (l, results, optDate))
		{
			string optionType ("") ;
			double strikePrice (-1.0) ;
			string dateKey (results[dateTag]) ;
			if (optionsTree.find (dateKey) == optionsTree.not_found()) 
				optionsTree.put_child (dateKey, pt::ptree()) ;

			pt::ptree& curTree = optionsTree.get_child (dateKey) ;
			bool pricesBegin (false) ;
			vector<double> prices ;

			while (getline (fin, l, '\n'))
			{
				IGNORE_BLANK_LINE(l) ;
				if (!optionType.empty() && strikePrice > 0.0)
				{
					string strikePriceStr ((format ("%1%") % strikePrice).str()) ;
					str::replace_all (strikePriceStr, ".", ",") ;
					string key ((format ("%1%.%2%") % optionType % strikePriceStr).str()) ;

					pt::ptree& typeTree = curTree.put_child (key, pt::ptree()) ;

					if (regex_match (l, results, price))
					{
						prices += lexical_cast<double>(results[priceTag]) ;
						pricesBegin = true ;
						continue ;
					} 
					else if (xpr::regex_match (l, results, nodata))
					{
						prices += -1.0 ;
						pricesBegin = true ;
						continue ;
					}
					else if (pricesBegin)
					{
						BOOST_FOREACH (int i, requiredOptionsIndices)
							typeTree.put (headings[i], prices[i-5]) ;
						break ;
					}
				}

				if (xpr::regex_match (l, results, optType))
				{
					optionType = optionTypeMap[results[typeTag]] ;
					continue ;
				}
				if (xpr::regex_match (l, results, optStrike))
				{
					strikePrice = lexical_cast<double> (results[strPriceTag]) ;
					continue ;
				}
			}
		}
	}

	pt::write_xml (cout, tree, pt::xml_writer_settings<char>(' ', 4)) ;
	fin.close() ;
}
