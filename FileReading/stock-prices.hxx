#ifndef STOCK_PRICES_HXX
#define STOCK_PRICES_HXX 1

#include <boost/iterator/zip_iterator.hpp>

typedef enum
{
	CurrentPrice = 0,
	DayOpen, 
	DayHigh,
	DayLow,
	PreviousDayClose,
	YearHigh,
	YearLow,
	NumberOfFields
} FieldId ;

typedef pair<string, FieldId> StringFieldPair ;
#define FIELD_ID(name) make_pair(BOOST_PP_STRINGIZE(name),name)

void fillValues (const boost::tuple<const string&, const double&>& p_tuple,
		pt::ptree& p_tree)
{
	p_tree.put (p_tuple.get<0>(), p_tuple.get<1>()) ;
}

#endif
