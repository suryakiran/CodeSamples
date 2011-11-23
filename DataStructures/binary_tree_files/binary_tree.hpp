#ifndef binary_tree_hpp
#define binary_tree_hpp 1

#include <iostream>
using namespace std;

class bst
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
    };

    node* m_root;
    node* m_lastVisited;
    bool find (int val, node* root);
    void printTree (node* root);
    void remove (int, node*);
    int height (node* root);
    bool isBalanced (node* root);

  public:
    bst();
    ~bst();

    bst& operator += (int val)
    {
      return insert(val);
    }

    bst& operator, (int val)
    {
      return insert(val);
    }

    pair<int, int> range (int);

    bst& insert (int val);
    bool find (int val);
    void print();
    int findMin ();
    int findMax() ;
    void remove (int val);
    bool isBalanced();
    int height();
};

#endif
