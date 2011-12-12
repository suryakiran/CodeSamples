#ifndef binary_tree_hpp
#define binary_tree_hpp 1

#include <std.hxx>

class bst
{
  public:
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

  private:
    typedef enum {
      LeftToRight = 0,
      RightToLeft
    } Direction;

    node* m_root;
    node* m_lastVisited;
    bool find (int val, node* root);
    void printTree (node* root);
    void remove (int, node*&);
    int numChildren (node* root);
    int findMin (node* root, int k);
    int height (node* root);
    bool isBalanced (node* root);
    bool isMirrorImage (node* left, node* right);
    void traverseZigZag (node* root, Direction d);
    void traverseLevel (node* root);
    node* commonAncestor (node* root, int p, int q);
    void morrisTraverse (node* root);

    void sumLeftRight (node *root);

    stack<node*> l2r, r2l; 

    bool isBST (node* root);

  public:
    bst();
    ~bst();

    void toLinkedList();

    bst& operator += (int val)
    {
      return insert(val);
    }

    bst& operator, (int val)
    {
      return insert(val);
    }

    bool isBST()
    {
      return isBST (m_root);
    }

    bool isMirrorImage()
    {
      return isMirrorImage(m_root->left, m_root->right);
    }

    void printToDot(const string& p_fileName) const;

    void traverseZigZag()
    {
      if (!m_root) 
        return;

      l2r.push (m_root);
      traverseZigZag (m_root, LeftToRight);
    }

    void morrisTraverse()
    {
      morrisTraverse (m_root);
    }

    void traverseLevel()
    {
      traverseLevel(m_root);
    }

    int commonAncestor (int p, int q)
    {
      node* n = commonAncestor (m_root, p, q);
      if (n)
        return n->m_value;
      else
        return numeric_limits<int>::max();
    }

    void convertToLinkedList();

    void sumLeftRight ()
    {
      sumLeftRight (m_root);
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
