#include <std.hxx>
#include <boost-multi-index.hxx>

struct Test
{
  string s;
  int i;
  float f;

  Test (const string& ps, int pi, float pf)
    : s(ps), i(pi), f(pf) { }
};

typedef multi_index_container <
  Test,
  indexed_by <
    ordered_unique < member <Test, string, &Test::s> >,
    ordered_unique < tag<int>, member <Test, int, &Test::i> >,
    ordered_unique < member <Test, float, &Test::f> >
    >
  > TestSet;

int main (void)
{
  TestSet s;
  s.insert (Test("Surya", 1, 0.1f));
  s.insert (Test("Kiran", 2, 0.2f));
  s.insert (Test("Gullapalli", 3, 0.3f));
  
  return 0;
}
