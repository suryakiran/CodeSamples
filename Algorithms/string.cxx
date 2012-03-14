#include "std.hxx"

void rev (char* s)
{
  char *p = s;
  char *q = s;

  for (; q && *q; ++q);
  --q;

  while (p < q) {
    char tmp = *p;
    *p = *q;
    *q = tmp;
    p++;
    q--;
  }
}

void rev (char* s, char* beg, char* end)
{
  char *p = beg;
  char *q ;

  if (!end) {
    for (q = beg; q && *q; ++q);
  } else {
    for (q = beg; (q && *q && (q != end)); ++q);
  }

  q--;

  while (p < q) {
    char tmp = *q;
    *q = *p;
    *p = tmp;
    p++;
    q--;
  }
}

void break_and_rev (char* s)
{
  rev (s, s, NULL);
  char* beg = s;
  char* end;

  do {
    for (end = beg; end && *end && !isspace(*end); ++end);
    rev (s, beg, end);
    while (end && isspace (*end)) { ++end; } ;
    beg = end;
  } while (end && *end);
}

int main (void)
{
  char *s = strdup ("Surya Kiran Gullapalli\0");
  break_and_rev (s);
  //rev(s, s, NULL);
//  rotate (s, 6);
  cout << s << endl;
}
