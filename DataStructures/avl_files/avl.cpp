#include <avl.hpp>

typedef enum {
  Left = 0,
  Right = 1
} Direction;

typedef enum {
  LeftToRight = 0,
  RightToLeft
} TraverseDirection;

struct avl_node
{
  avl_node* m_left;
  avl_node* m_right;

  int m_height;
  int m_val;

  avl_node(int p_val)
    : m_left(0), m_right(0),
      m_height(0), m_val(p_val)
  {
  }
};

namespace {

  int fileNum (0);

  string dotNode (avl_node* node, int nodeNum)
  {
    return 
    (boost::format ("node%1% [label=<\n\
        <TABLE>\n\
        <TR>\n\
        <TD bgcolor=\"green\" colspan=\"2\" port=\"left\"></TD>\n\
        <TD bgcolor=\"white\" colspan=\"10\" port=\"center\">%2%</TD>\n\
        <TD bgcolor=\"red\" colspan=\"2\" port=\"right\"></TD>\n\
        </TR>\n\
        </TABLE>\n\
        >]") % nodeNum % node->m_val).str();
  }

  template <class T>
  void toDot (const string& p_fileName, const T& label, avl_node* root)
  {
    fstream fout ;
    fout.open (p_fileName.c_str(), ios_base::out);
    fout << "digraph \"\" {" << endl;
    fout << "node [shape=plaintext];" << endl;
    fout << boost::format ("\tlabel=\"%1%\"") % label << endl;
    queue < pair <avl_node*, int> > nodes;
    nodes.push (make_pair (root, 0));

    int i(0);
    while (!nodes.empty())
    {
      pair<avl_node*, int>& node = nodes.front();
      fout << dotNode (node.first, node.second) << endl;

      if (node.first->m_left) {
        nodes.push (make_pair (node.first->m_left, ++i));
        fout << boost::format ("node%1%:left -> node%2%:center") % node.second % i << endl;
      }

      if (node.first->m_right) {
        nodes.push (make_pair (node.first->m_right, ++i));
        fout << boost::format ("node%1%:right -> node%2%:center") % node.second % i << endl;
      }

      nodes.pop();
    }

    fout << "}" << endl;
    fout.close();
  }

  int height (avl_node* root)
  {
    return root ? root->m_height : -1;
  }

  void traverseZigZagOrder (stack<avl_node*>& curStack, stack<avl_node*>& childStack, TraverseDirection d)
  {
    while (!curStack.empty())
    {
      avl_node* node = curStack.top();
      cout << boost::format ("(%1%, %2%)") % node->m_val % node->m_height << endl;
      switch (d)
      {
        case LeftToRight:
          if (node->m_left) {
            childStack.push (node->m_left);
          }
          if (node->m_right) {
            childStack.push (node->m_right);
          }
          break;
        case RightToLeft:
          if (node->m_right) {
            childStack.push (node->m_right);
          }
          if (node->m_left) {
            childStack.push (node->m_left);
          }
          break;
        default:
          break;
      }
      curStack.pop();
    }

    if (!childStack.empty()) {
      d = (d == LeftToRight) ? RightToLeft : LeftToRight;
      traverseZigZagOrder (childStack, curStack, d);
    }
  }

  void traverseZigZagOrder (avl_node* root)
  {
    if (!root) {
      return;
    }

    stack <avl_node*> s;
    stack <avl_node*> cs;
    s.push (root);

    traverseZigZagOrder (s, cs, RightToLeft);
  }

  void traverseLevelOrder (avl_node* root)
  {
    if (!root) {
      return;
    }

    queue<avl_node*> q;
    q.push (root);

    while (!q.empty())
    {
      avl_node* node = q.front();

      if (node->m_left) {
        q.push (node->m_left);
      }

      if (node->m_right) {
        q.push (node->m_right);
      }

      cout << boost::format ("(%1%, %2%)") % node->m_val % node->m_height << endl;

      q.pop();
    }
  }

  void singleRotateChild (Direction d, avl_node*& k2)
  {
    cout << "Single Rotation Needed " << k2->m_val << endl;
    avl_node* k1;
    switch (d)
    {
      case Left:
        k1 = k2->m_left;
        k2->m_left = k1->m_right;
        k1->m_right = k2;
        k2->m_height = 1 + max (height(k2->m_right), height(k2->m_left));
        k1->m_height = 1 + max (height(k1->m_left), k2->m_height); 
        k2 = k1;
        break;
      case Right:
        k1 = k2->m_right;
        k2->m_right = k1->m_left;
        k1->m_left = k2;
        k2->m_height = 1 + max (height(k2->m_right), height(k2->m_left));
        k1->m_height = 1 + max (height(k1->m_left), k2->m_height); 
        k2 = k1;
        break;
      default:
        break;
    }
  }

  void doubleRotateChild (Direction d, avl_node*& root)
  {
    cout << "Double Rotation Needed " << root->m_val << endl;
    switch (d) 
    {
      case Left:
        singleRotateChild (Right, root->m_left);
        singleRotateChild (Left, root);
        break;
      case Right:
        singleRotateChild (Left, root->m_right);
        singleRotateChild (Right, root);
        break;
      default:
          break;
    }
  }

  void print (avl_node* root)
  {
    if (!root) {
      return;
    }

    print (root->m_left);
    cout << boost::format ("(%1%, %2%)") % root->m_val % root->m_height << endl;
    print (root->m_right);
  }
  
  int size (avl_node* root)
  {
    int sum (0);

    if (!root) {
      return 0;
    }

    sum = 1 + size (root->m_left) + size (root->m_right); 
    return sum;
  }

  void insert (avl_node*& root, int val, avl_node* p_root)
  {
    if (!root) {
      root = new avl_node (val);
    } else if (val < root->m_val) {
      insert (root->m_left, val, p_root);
      if (height (root->m_left) - height(root->m_right) == 2) {
        if (val < root->m_left->m_val) {
          fileNum++;
          string beforeFileName = (boost::format ("before-single-rotate-%1%.gv") % fileNum).str();
          string afterFileName = (boost::format ("after-single-rotate-%1%.gv") % fileNum).str();
          ::toDot (beforeFileName, boost::format ("Rotate Left (Inserting %1%)") % val, p_root);
          singleRotateChild (Left, root);
          ::toDot (afterFileName, boost::format ("Rotate Left (Inserted %1%)") % val, p_root);
        } else {
          fileNum++;
          string beforeFileName = (boost::format ("before-double-rotate-%1%.gv") % fileNum).str();
          string afterFileName = (boost::format ("after-double-rotate-%1%.gv") % fileNum).str();
          ::toDot (beforeFileName, boost::format ("Double Rotate Left (Inserting %1%)") % val, p_root);
          doubleRotateChild (Left, root);
          ::toDot (afterFileName, boost::format ("Double Rotate Left (Inserted %1%)") % val, p_root);
        }
      }
    } else if (val > root->m_val) {
      insert (root->m_right, val, p_root);
      if (height (root->m_right) - height(root->m_left) == 2) {
        if (val > root->m_right->m_val) {
          fileNum++;
          string beforeFileName = (boost::format ("before-single-rotate-%1%.gv") % fileNum).str();
          string afterFileName = (boost::format ("after-single-rotate-%1%.gv") % fileNum).str();
          ::toDot (beforeFileName, boost::format ("Rotate Right (Inserting %1%)") % val, p_root);
          singleRotateChild (Right, root);
          ::toDot (afterFileName, boost::format ("Rotate Right (Inserted %1%)") % val, p_root);
        } else {
          string beforeFileName = (boost::format ("before-double-rotate-%1%.gv") % fileNum).str();
          string afterFileName = (boost::format ("after-double-rotate-%1%.gv") % fileNum).str();
          ::toDot (beforeFileName, boost::format ("Double Rotate Right (Inserting %1%)") % val, p_root);
          doubleRotateChild (Right, root);
          ::toDot (afterFileName, boost::format ("Double Rotate Right (Inserted %1%)") % val, p_root);
        }
      }
    } else {
      return;
    }
    root->m_height = max(height(root->m_left), height (root->m_right)) + 1;
  }

  bool find (avl_node* root, int val)
  {
    if (!root) {
      return false;
    } else if (val < root->m_val) {
      return (root->m_left, val);
    } else if (val > root->m_val) {
      return (root->m_right, val);
    } else {
      return true;
    }
  }
}

avl::avl()
  :m_root(0), m_lastVisited(0)
{
}

avl::~avl()
{
}

avl& avl::insert (int p_val)
{
  if (!m_root) {
    m_root = new avl_node(p_val);
    m_root->m_val = p_val;
  } else {
    ::insert (m_root, p_val, m_root);
  }

  return *this;
}

void avl::remove (int p_val)
{
}

bool avl::find (int p_val)
{
  ::find (m_root, p_val);
}

int avl::size () const
{
  if (!m_root) {
    return 0;
  }

  return (1 + ::size(m_root->m_left) + ::size(m_root->m_right));
}

bool avl::isAvl() const
{
  return true;
}

int avl::height () const
{
  return 1 + max (::height(m_root->m_left), ::height(m_root->m_right));
}

void avl::print () const
{
  if (!m_root) {
    return ;
  }

  ::print (m_root->m_left);
  cout << boost::format ("(%1%, %2%)") % m_root->m_val % m_root->m_height << endl;
  ::print (m_root->m_right);
}

void avl::traverse (TraverseType t) const
{
  switch (t)
  {
    case InOrder:
      print();
      break;
    case PreOrder:
      break;
    case PostOrder:
      break;
    case LevelOrder:
      ::traverseLevelOrder(m_root);
      break;
    case ZigZagOrder:
      ::traverseZigZagOrder (m_root);
      break;
  }
}
