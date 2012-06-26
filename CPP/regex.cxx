#include "std.hxx"
#include <boost/regex.hpp>
#include <QtCore/QString>

int main (void)
{
  boost::regex regex ("\\s*([^\\s]*)\\s*\\(([^\\)]*)\\)");
  boost::smatch match;
  QString s (" abc (http://def.ghi/pqr.com)");
  string ss (s.toStdString());
  if (boost::regex_match (ss, match, regex))
  {
    cout << match[0] << endl;
  }
}
