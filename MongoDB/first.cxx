#include <mongo/client/dbclient.h>
#include <std.hxx>

void run()
{
  mongo::DBClientConnection c;
  mongo::HostAndPort host("ds027708.mongolab.com:27708");
  string error;
  try {
    c.connect(host, error);
    if (c.auth("dummy", "readwriteuser", "readwriteuserabc", error)) {
      cout << "Authenticated" << endl;
    } else {
      cout << "Authentication Failed" << endl;
    }
  } catch (const mongo::DBException& e) {
    cout << "Exception: " << e.what() << endl;
  }
}

int main (void)
{
  run();
  return 0;
}
