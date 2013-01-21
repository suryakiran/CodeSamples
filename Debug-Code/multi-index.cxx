#include <std.hxx>
#include <boost-multi-index.hpp>

struct Test
{
  Test (const string& ps, int pi, float pf)
    : s(ps), i(pi), f(pf)
  {
  }

  friend ostream& operator<< (ostream& os, const Test& t)
  {
    os << format(" (%1%, %2%, %3%)") % t.s % t.i % t.f;
    return os;
  }
  
  string s;
  int i;
  float f;
};

template <class T>
void get_type (const T& t)
{
  const T& cp = t;
  return;
}

typedef multi_index_container <
  Test,
  indexed_by <
    ordered_unique < member <Test, string, &Test::s> >,
    ordered_unique < tag<int>,  member <Test, int, &Test::i> >,
    ordered_unique < member <Test, float, &Test::f> >
    >
  > TestSet;

int main(void)
{
  TestSet ts;
  ts.insert(Test("Surya", 10, 1.0f));
  ts.insert(Test("Kiran", 5, 2.0f));
  ts.insert(Test("Gullapalli", 7, 0.3f));

  BOOST_AUTO (tsBegin, boost::begin(ts));
  BOOST_AUTO (tsBeginRef, *tsBegin);
  BOOST_AUTO (const& tsIdx, ts.get<int>());
  TestSet::index_type_list itl;
  printContainer("Multi Index Container", ts);
  return 0;
}
