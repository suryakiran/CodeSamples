#include "std.hxx"
#include "boost-xpressive.hxx"
#include "file-reading.hxx"
#include "stock-prices.hxx"

#include <boost/assign/std/set.hpp>
#include <boost/assign/list_inserter.hpp>
#include <bitset>
using namespace boost::assign ;

int main (int argc, char** argv)
{
	parse_args (argc, argv) ;
	fs::fstream fin ;
	fin.open (inputFile, ios_base::in | ios_base::binary) ;

	map<string, StringFieldPair> validFields ;
	insert (validFields) 
		("Open Price", FIELD_ID(DayOpen))
		("High Price", FIELD_ID(DayHigh))
		("Low Price", FIELD_ID(DayLow))
		("52 Wk High", FIELD_ID(YearHigh))
		("52 Wk Low", FIELD_ID(YearLow))
		("Prev Close", FIELD_ID(PreviousDayClose))
		("Current Price", FIELD_ID(CurrentPrice))
		;

	typedef map<string, StringFieldPair>::value_type ValidFieldMap ;
	vector<string> fields(validFields.size());

	BOOST_FOREACH (const ValidFieldMap& vfm, validFields)
		fields[vfm.second.second] = vfm.second.first;

	xpr::smatch results ;
	string l ;

	xpr::mark_tag textTag(1), priceTag(1) ;
	pt::ptree tree ;
	pt::ptree& nseTree = tree.put_child ("Scrip.PriceDetails.Nse", pt::ptree()) ;
	pt::ptree& bseTree = tree.put_child ("Scrip.PriceDetails.Bse", pt::ptree()) ;

	xpr::sregex validText =
		as_xpr(*(~(xset= '<','&',';'))) ;

	xpr::sregex td = 
		beginTag("strong", true, false) >> *_s
		>> (textTag= validText) >> *_s >> '<'
		;

	xpr::sregex th = 
		beginTag("th") >> *_s
		>> (textTag= validText) >> *_s >> endTag("th")
		;

	xpr::sregex tdPrice =
		beginTag("td") >> *_s
		>> (priceTag = floatNumber) >> *_s >> endTag("td")
		;

	xpr::sregex thPrice =
		beginTag("th") >> *_s
		>> (priceTag = floatNumber) >> *_s >> endTag("th") ;

	xpr::sregex curPriceReg =
		beginTag("div", true, false) >> *_s >> beginTag("p") >> *_s
		>> beginTag("strong", true, false) >> *_s 
		>> (priceTag= floatNumber) >> *_s >> endTag("strong") >> *_s 
		>> endTag("p")
		;

	vector<xpr::sregex> tabObjs ;
	tabObjs.push_back(td);
	tabObjs.push_back(th);

	vector<xpr::sregex> priceRegs ;
	priceRegs.push_back(tdPrice);
	priceRegs.push_back(thPrice);

	vector<double> bsePrices(validFields.size(), 0.0), nsePrices(validFields.size(), 0.0) ;
	bitset<NumberOfFields> bseFields(0), nseFields(0) ;

	while (getline (fin, l, '\n'))
	{
		IGNORE_BLANK_LINE(l) ;
		str::erase_all (l, ",");

		bool tagFound(false);
		if (xpr::regex_match (l, results, curPriceReg))
		{
			fields[CurrentPrice] = "CurrentPrice";
			if (bseFields.test(CurrentPrice)) 
			{
				nsePrices[CurrentPrice] = lexical_cast<double>(results[priceTag]);
				nseFields.set(CurrentPrice);
			}
			else
			{
				bsePrices[CurrentPrice] = lexical_cast<double>(results[priceTag]);
				bseFields.set(CurrentPrice);
			}
			continue ;
		}

		BOOST_FOREACH(xpr::sregex reg, tabObjs)
		{
			if (xpr::regex_search (l, results, reg))
			{
				tagFound = true ;
				string field (results[textTag]);
				str::trim(field) ;
				str::erase_all(field, ".") ;
				if (validFields.count(field))
				{
					int idx(validFields[field].second);

					vector<double>& prices = bseFields.test(idx) ? nsePrices : bsePrices ;

					if (bseFields.test(idx)) nseFields.set(idx) ;
					else                     bseFields.set(idx);

					while(getline(fin, l, '\n'))
					{
						IGNORE_BLANK_LINE(l);
						str::erase_all(l, ",");
						if (l.empty())
							continue ;
						bool priceFound (false);
						BOOST_FOREACH(xpr::sregex priceReg, priceRegs)
						{
							if (xpr::regex_match(l, results, priceReg))
							{
								priceFound = true ;
								prices[idx] = lexical_cast<double>(results[priceTag]);
								break ;
							} 
							else if (xpr::regex_match(l, results, endTag("tr")))
							{
								priceFound = true;
								break ;
							}
						}
						if (priceFound)
							break ;
					}
				}
			}
			if (tagFound) break ;
		}
		if (tagFound) continue ;
	}

	std::for_each (
		boost::make_zip_iterator (boost::make_tuple(fields.begin(), nsePrices.begin())),
		boost::make_zip_iterator (boost::make_tuple(fields.end(), nsePrices.end())),
		phx::bind (fillValues, pha::arg1, phx::ref(nseTree))
		) ;

	std::for_each (
		boost::make_zip_iterator (boost::make_tuple(fields.begin(), bsePrices.begin())),
		boost::make_zip_iterator (boost::make_tuple(fields.end(), bsePrices.end())),
		phx::bind (fillValues, pha::arg1, phx::ref(bseTree))
		) ;
	pt::write_xml (cout, tree, pt::xml_writer_settings<char>(' ', 4)) ;
	fin.close() ;
}
