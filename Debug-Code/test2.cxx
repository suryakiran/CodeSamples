#include "std.hxx"

struct ContextSpreadsheetModel
{
  struct Item {
    int id;
    string groupHint;

    Item()
    {
      id = 13;
      groupHint = "Surya Kiran";
    }
  };

  Item i;
};

int main (void)
{
  list<ContextSpreadsheetModel> ls;
  ls.push_back (ContextSpreadsheetModel());
  ls.push_back (ContextSpreadsheetModel());
  ls.push_back (ContextSpreadsheetModel());
  ls.push_back (ContextSpreadsheetModel());
  ls.push_back (ContextSpreadsheetModel());
  return 0;
}
