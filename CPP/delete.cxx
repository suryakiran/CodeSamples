#include "std.hxx"

int main (void)
{
  cout << "Delete null pointer" << endl;
  double* d = 0;
  delete d;

  cout << "Delete empty pointer" << endl;
  int *i;
  //delete i;

  cout << "Double Delete" << endl;
  float* f = new float(5.0f);
  delete f;
  f = 0;
  delete f;
}
