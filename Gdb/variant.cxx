#include <Qt/QtCore>

int main (void)
{
  QSettings settings ("Surya Org", "Test App");
  settings.setValue ("level/anchor(http://surya/@kiran/gullapalli.com)", "Sandbox::1");
  settings.remove ("Sandbox::2");
  QStringList sl;
  sl << "Surya" << "Kiran" << "Gullapalli";
  QVariant v(sl);
  v = 1.0;
  v = "Surya Kiran";
  return 0;
}
