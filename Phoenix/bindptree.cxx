#include "phoenix.hxx"
#include <std.hxx>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree ;

int main (void)
{
	pt::ptree tree ;
	phx::bind(&pt::ptree::put<string, bool>, tree, string("Temp.Flag"), true) ;
}
