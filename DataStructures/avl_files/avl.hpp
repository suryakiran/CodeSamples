#ifndef avl_hpp_INCLUDED
#define avl_hpp_INCLUDED

#include <std.hxx>

struct avl_node;

class avl
{
  public:
    avl();
    ~avl();

    avl& insert (int);
    void remove (int);
    bool find (int);

    int size () const;
    bool isAvl() const;
    int height () const;

  private:
    avl_node *m_root;
    avl_node *m_lastVisited;
};

#endif
