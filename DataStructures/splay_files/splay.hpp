#ifndef splay_hpp
#define splay_hpp 1

#include <std.hxx>

struct splay_node;

typedef boost::add_pointer<splay_node>::type  Node;
typedef boost::add_reference <Node>::type NodeRef;

class splay
{
  private:
    Node m_root, m_null;
    bool find (int val, NodeRef root, NodeRef parent);
    void printTree (Node root);
    void remove (int, Node);
    void rotateRight(Node);
    void rotateLeft(Node);
//    bool splayNode (Node);
    void splayNode (Node);

    int m_fileNum;
    size_t m_numItems;

  public:
    splay();
    ~splay();

    splay& operator += (int val)
    {
      return insert(val);
    }

    size_t size() const {
      return m_numItems;
    }

    splay& operator, (int val)
    {
      return insert(val);
    }

    pair<int, int> range (int);

    splay& insert (int val);
    bool find (int val);
    void print(const string& p_label);
    int findMin ();
    int findMax() ;
    void remove (int val);
};

#endif
