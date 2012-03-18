#ifndef SLIST_HPP
#define SLIST_HPP

#include <std.hxx>

struct slist_node;
typedef slist_node* Node;

class slist
{
  public:
    slist()
      : m_head (0), m_fileNum (0)
    {
    }

    ~slist();

    void push (int i);
    void print ();
    void reverse();

  private:
    Node m_head;
    unsigned short m_fileNum;
};

#endif
