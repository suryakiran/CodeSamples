#include "std.hxx"

int main (void)
{
  vector < auto_ptr <int> > intpVec;
  intpVec.push_back (new int(5));
  intpVec.push_back (new int(10));
}
