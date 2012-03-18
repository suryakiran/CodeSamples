#include <std.hxx>

void replace (char* str, char *rep)
{
  int spaces (0);
  char *s = str;
  while (s && *s)
  {
    if (isspace (*s++))
      spaces++;
  }

  int length (strlen(str));
  int newLength = length + (spaces * 2) + 1;

  cout << "Spaces: " << spaces << endl;

  s = str;
  for (int i = length - 1, j = newLength - 1; i >= 0; i--, j--)
  {
    if (s[i] == ' ')
    {
      s[j] = rep[2];
      s[--j] = rep[1];
      s[--j] = rep[0];
    }
    else
    {
      s[j] = s[i];
    }
  }
  s[newLength] = '\0';
}

int main(void)
{
  char *s = strdup ("Surya Kiran Gullapalli");
  replace (s, "012");

  printf ("Str Length: %d, string: %s\n", strlen(s), s);
}
