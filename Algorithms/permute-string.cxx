#include <std.hxx>
int i (0);

stl::IntStringMap smap;

void permute_string_repeat (string leading, string trailing = "")
{
  if (trailing.length() == 1) {
    smap.insert (make_pair (++i, leading + trailing));
    return;
  }

  if (trailing.empty()) {
    swap (leading, trailing);
  }

  for (int i = 0; i < trailing.length(); ++i)
  {
    swap (trailing[i], trailing[0]);
    permute_string_repeat (leading+trailing[0], trailing.substr (1, trailing.length()-1));
  }
}

void permute_string_unique (string leading, string trailing = "")
{
  if (trailing.length() == 1) {
    smap.insert (make_pair (++i, leading + trailing));
    return;
  }

  if (trailing.empty()) {
    swap (leading, trailing);
  }

  for (int i = 0; i < trailing.length(); ++i)
  {
    char c = trailing[i];
    bool charFound (false);
    for (int k = 0; k < i; ++k)
    {
      if (trailing[k] == c) {
        charFound = true;
        break;
      }
    }

    if (charFound) {
      continue;
    }
    swap (trailing[i], trailing[0]);
    permute_string_repeat (leading+trailing[0], trailing.substr (1, trailing.length()-1));
  }
}

int main (void)
{
  permute_string_unique ("SSuryaa");
  BOOST_FOREACH (stl::IntStringMapValue v, smap)
    cout << boost::format ("(%1%, %2%)") % v.first % v.second << endl;
  cout << smap.size() << endl;
}
