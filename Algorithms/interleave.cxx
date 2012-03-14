#include "std.hxx"

bool isInterleaved (char* a, char* b, char* c)
{
  if (!(*a || *b || *c)) {
    return true;
  }

  if (!(*c)) {
    return false;
  }

  return (
      ((*c == *a) && isInterleaved (a+1, b, c+1)) ||
      ((*c == *b) && isInterleaved (a, b+1, c+1))
      );
}

void printInterleave (char* a, char* b, string s, int idx)
{
  if (!(*a || *b)) {
    cout << s << endl;
    s.clear();
    return;
  }

  if (*a) {
    s[idx] = *a;
    printInterleave (a+1, b, s, idx+1);
  }

  if (*b) {
    s[idx] = *b;
    printInterleave (a, b+1, s, idx+1);
  }
}

void printInterleave1 (char* a, char* b)
{
  string s;
  s.resize (strlen(a) + strlen (b));
  printInterleave (a, b, s, 0);
}

int main (void)
{
  cout << boolalpha; 
  cout << isInterleaved (strdup("AAB"), strdup("AAC"), strdup("AACAAB")) << endl;

  printInterleave1 (strdup ("ABC"), strdup ("XYZ"));
}
