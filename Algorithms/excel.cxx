#include "std.hxx"

DEFINE_MAP (int, char, IntCharMap);
IntCharMap icm;

struct FunObj
{
  FunObj ()
    : m_value(0) { }

  void operator() (char c)
  {
    m_value = (m_value * 26) + static_cast<int> (c - ('A'-1));
  }

  int m_value ;
};

int main (void)
{
  string s = "AAA";

  insert (icm) 
    (1, 'A')
    (2, 'B')
    (3, 'C')
    (4, 'D')
    (5, 'E')
    (6, 'F')
    (7, 'G')
    (8, 'H')
    (9, 'I')
    (10, 'J')
    (11, 'K')
    (12, 'L')
    (13, 'M')
    (14, 'N')
    (15, 'O')
    (16, 'P')
    (17, 'Q')
    (18, 'R')
    (19, 'S')
    (20, 'T')
    (21, 'U')
    (22, 'V')
    (23, 'W')
    (24, 'X')
    (25, 'Y')
    (26, 'Z')
    ;

  int num = 856;
  FunObj fun;
  fun = for_each (s.begin(), s.end(), fun);
  cout << fun.m_value << endl;
}
