#ifndef DLIST_HPP
#define DLIST_HPP

#include <std.hxx>

struct dlist_node;
typedef dlist_node* Node;

class dlist
{
  public:
    dlist()
      : m_head (0), m_fileNum (0)
    {
    }

    void push (int i);
    void print ();
    void reverse();

  private:
    Node m_head;
    unsigned short m_fileNum;
};

#endif
