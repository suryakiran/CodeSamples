#include <std.hxx>

namespace test {
  struct Test
  {
    Test() : m_i(13){ }
    int value() {
      return m_i;
    }

    int m_i;
  };
}

int main (void)
{
  cout << "Debug Sample for namespace" << endl;
  test::Test t;
  cout << t.value() << endl;
}
