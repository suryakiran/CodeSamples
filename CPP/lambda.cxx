#include <std.hxx>

int main (void)
{
  stl::IntStringMap m;
  insert(m)
    (1, "Surya")
    (2, "Kiran")
    (3, "Gullapalli")
    ;

  bool found(false);
  rng::for_each (m,
                 [&found](const stl::IntStringMapValue& value) {
                   if (value.second == "Kiran") {
                     found = true;
                     return;
                   }
                   cout << value.second << endl;
                 });
  cout << boolalpha;
  cout << found << endl;
}
