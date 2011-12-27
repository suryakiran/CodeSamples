#include <std.hxx>

int main (void)
{
  stl::IntVector vi;
  vi += 1,2,3,4,5,6,7,8,9,10;
  printContainer ("Vector", vi);
  cout << endl;

  deque<int> di;
  di += 1,2,3,4,5;
  printContainer ("Deque", di);
  cout << endl;

  stl::IntList vl;
  vl += 1,2,3,4,5,6,7,8,9,10;
  printContainer ("List", vl);
  cout << endl;

  stl::IntSet vs;
  insert(vs)(10)(4)(2)(3)(7)(5)(6)(9)(8)(1);
  printContainer ("Set", vs);
  cout << endl;

  stl::IntStringMap vm;
  insert(vm)(1, "Surya") (2, "Kiran")(3, "Gullapalli");
  printContainer ("Map", vm);
  cout << endl;

  int a[] = {1, 2, 3, 4, 5};
  printContainer ("Array", a);
  cout << endl;
}
