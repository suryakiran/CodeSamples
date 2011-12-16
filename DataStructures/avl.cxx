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
    .insert(6).insert(16).insert (17);
  t.print ("Insertion Done");

  t.insert (13);
  t.print ("Insert 13");

  t.insert (12);
  t.print ("Insert 12");

  t.insert (11);
  t.print ("Insert 11");

  t.remove (14);
  t.print ("Remove 14");
#if 0
  for (int i = 50; i < 1001; i += 10)
    t.insert (i);

  t.print ("Insert bunch");
#endif
}
