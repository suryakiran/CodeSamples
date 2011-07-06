#include <iostream>
#include <vector>
#include <algorithm>

#include <boost/iterator/zip_iterator.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_statement.hpp>
#include <boost/spirit/include/phoenix_scope.hpp>
#include <boost/spirit/home/phoenix/function/function.hpp>

using namespace boost::phoenix;
using namespace boost::phoenix::arg_names;
using namespace boost::phoenix::local_names;
using namespace std;
namespace fusion = boost::fusion;

struct print_tuple {
	void operator()(const boost::tuple<int&, int&>& t) const {
		cout << t.get<0>() << " " << t.get<1>() << "\n";
	}
};

struct get0_ {
	template<typename Arg>
		struct result {
			typedef int type;
		};

	template<typename Arg>
		int operator()(Arg a1) const {
			return a1.get<0>();
		}
};

function<get0_> get0;

int main()
{
	vector<int> a(10), b(10);

	for(unsigned i=0, e=a.size(); i!=e; ++i) {
		a[i] = i;
		b[i] = i;
	}

	std::for_each(a.begin(), a.end(), cout << arg1);

	std::for_each(boost::make_zip_iterator(boost::make_tuple(a.begin(),
					b.begin())),
			boost::make_zip_iterator(boost::make_tuple(a.end(),
					b.end())), cout << get0(arg1));
}
