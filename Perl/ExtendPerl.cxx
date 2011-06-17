#include <std.h>

class Test
{
  public:
    Test () 
      :m_i (5)
    {
      cout << "Test Constructor" << endl;
    }

    ~Test ()
    {
      cout << "Test Destructor" << endl;
    }

    const int& getInt () const {
      return m_i;
    }

    void setInt (const int& p_i) {
      m_i = p_i;
    }

    void print () 
    {
      cout << "Integer Value Stored: " << m_i << endl;
    }

  private:
    int m_i;
};

int main (void) 
{
  cout << "Extend Perl" << endl;
  Test t;
  t.print();
}
