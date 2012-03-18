#ifndef avl_hpp_INCLUDED
#define avl_hpp_INCLUDED

#include <std.hxx>

struct avl_node;

typedef avl_node Node;
typedef boost::add_pointer<avl_node>::type NodePtr;
typedef boost::add_reference<NodePtr>::type NodeRef;

typedef enum {
  PreOrder = 0,
  InOrder,
  PostOrder,
  LevelOrder,
  ZigZagOrder
} TraverseType;

class avl
{
  public:
    avl();
    ~avl();

    avl& insert (int);
    void remove (int);
    bool find (int);
    void print (const string& p_label) const ;

    int size () const;
    bool isAvl() const;
    int height () const;

    void traverse (TraverseType t) const;

  private:
    avl_node *m_root;
    avl_node *m_lastVisited;
};

#endif
