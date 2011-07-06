#include "std.hxx"
using namespace std ;

#include <boost/spirit/include/phoenix.hpp>
namespace phx = boost::phoenix ;
namespace pha = phx::arg_names ;

#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>

#include <boost/iterator/zip_iterator.hpp>
#include <boost/assign.hpp>
using namespace boost::assign ;

void updateOut (const boost::tuple<const string&, const int&>& p_tuple, vector<string>& p_out)
{
	ostringstream os ;
	os << p_tuple.get<0>() << '-' << p_tuple.get<1>();
	p_out += os.str() ;
}

int main (void)
{
	vector<string> vs, out ;
	vector<int> vi, vi2 ;

	vs += "String", "String", "String", "String", "String";
	vi += 1,2,3,4,5 ;

	vector<string>::iterator sbegIter = vs.begin();
	vector<string>::iterator sendIter = vs.end();

	vector<int>::iterator ibegIter = vi.begin();
	vector<int>::iterator iendIter = vi.end();

	std::for_each (
			boost::make_zip_iterator(boost::make_tuple(sbegIter, ibegIter)),
			boost::make_zip_iterator(boost::make_tuple(sendIter, iendIter)),
			boost::lambda::bind (&updateOut, boost::lambda::_1, boost::ref(out))
			) ;

	printContainer ("Output", out);
}
