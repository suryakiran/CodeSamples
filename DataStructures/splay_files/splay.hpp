#ifndef splay_hpp
#define splay_hpp 1

#include <iostream>
using namespace std;

class splay
{
  private:
    struct node
    {
      node(int v)
        : m_value(v), left(0), right(0)
      {
      }

      int m_value;
      node* left;
      node* right;
      node* parent;
    };

    node* m_root;
    node* m_lastVisited;
    bool find (int val, node* root);
    void printTree (node* root);
    void remove (int, node*);
    void rotateRight(node*);
    void rotateLeft(node*);

  public:
    splay();
    ~splay();

    splay& operator += (int val)
    {
      return insert(val);
    }

    splay& operator, (int val)
    {
      return insert(val);
    }

    pair<int, int> range (int);

    splay& insert (int val);
    bool find (int val);
    void print();
    int findMin ();
    int findMax() ;
    void remove (int val);
};

#endif
