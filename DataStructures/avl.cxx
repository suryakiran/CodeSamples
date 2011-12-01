#include <avl.hpp>

int main (void)
{
  cout << boolalpha;
  avl t;
  t
    .insert(10).insert(5) .insert(25)
    .insert(30).insert(15).insert(4)
    .insert(24).insert(26).insert(35)
    .insert(1) .insert(14).insert(3)
    .insert(6).insert(16);

  cout << t.size() << endl;
  cout << t.height() << endl;
}
