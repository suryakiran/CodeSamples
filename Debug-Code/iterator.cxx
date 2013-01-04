#include <std.hxx>

int main (void)
{
  map<string,int> m;
  
  map<string, int>::iterator iter;
  m["Surya"] = 1;
  m["Kiran"] = 2;

  string s("Surya Kiran Gullapalli");
  
  iter = m.find("Surya");
  iter = m.find("Kiran");
  iter = m.find("Gullapalli");
  
  if (iter == m.end()) {
    cout << "Invalid Iterator" << endl;
  }
}
