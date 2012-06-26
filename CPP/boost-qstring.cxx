#include "std.hxx"
#include <QtCore/QString>

int main (void)
{
  vector<string> vs;
  std::string s ("basement.level,http://web.studio.dreamworks.com/data/@show/turbo/@project/shot_turbo_sqpersonal_kihong_test_basement/@version/5eakj7b (http://web.studio.dreamworks.com/data/@sandbox/802fb9977c624a16ac84bbdd3987182e)");
  str::split (vs, s, boost::is_any_of (", ()"), boost::token_compress_on);
  printContainer ("Result", vs, '#');
}
