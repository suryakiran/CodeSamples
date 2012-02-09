#include <point.hxx>

int main (void)
{
  Point2d p2 (3.0, 4.0);
  Point3d p3 (3.0, 4.0, 5.0);

  p3.x() = 10.0;
  p2.y() = 19.0;

  cout << p2 << endl;
  cout << p3 << endl;

  return 0;
}
