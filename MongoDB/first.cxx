#include <mongo/client/dbclient.h>
#include <std.hxx>

void run()
{
  mongo::DBClientConnection c;
  c.connect("localhost");
}

int main (void)
{
  try {
    run();
    cout << "Connected Ok" << endl;
  } catch (const mongo::DBException& e) {
    cout << "Caught Exception: " << e.what() << endl;
  }
  return 0;
}
