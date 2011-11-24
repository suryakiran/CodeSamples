#ifndef binary_tree_hpp
#define binary_tree_hpp 1

#include <std.hxx>

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

      ~node()
      {
        cout << "Node Destructor" << endl;
      }
    };

    typedef node* nodep;

    typedef enum {
      LeftToRight = 0,
      RightToLeft
    } Direction;

    nodep m_root;
    nodep m_lastVisited;
    bool find (int val, nodep root);
    void printTree (nodep root);
    void remove (int, nodep);
    int numChildren (nodep root);
    int findMin (nodep root, int k);
    int height (nodep root);
    bool isBalanced (nodep root);
    bool isMirrorImage (nodep left, nodep right);
    void traverseZigZag (nodep root, Direction d);
    void traverseLevel (nodep root);

    stack<nodep> l2r, r2l; 

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

    bool isMirrorImage()
    {
      return isMirrorImage(m_root->left, m_root->right);
    }

    void traverseZigZag()
    {
      if (!m_root) 
        return;

      l2r.push (m_root);
      traverseZigZag (m_root, LeftToRight);
    }

    void traverseLevel()
    {
      traverseLevel(m_root);
    }

    pair<int, int> range (int);

    bst& insert (int val);
    bool find (int val);
    void print();
    int findMin ();
    int findMin (int) ;
    int findMax() ;
    void remove (int val);
    bool isBalanced();
    int height();
};

#endif
