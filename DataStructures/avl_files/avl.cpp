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
  NodePtr m_left;
  NodePtr m_right;

  int m_height;
  int m_val;
  int m_calcHeight;

  avl_node(int p_val)
    : m_left(0), m_right(0),
      m_height(0), m_val(p_val),
      m_calcHeight(0)
  {
  }

  bool isLeaf() {
    if (m_left || m_right) {
      return false;
    }
    return true;
  }

};

namespace {

  int fileNum (0);
  fmt fileNameFmt (fmt("avl-%1%.gv"));

  int calcHeight (NodePtr root)
  {
    if (!root) {
      return -1;
    }

    if (root->isLeaf()) {
      root->m_calcHeight = 0;
      return 0;
    } 

    int h = 1 + max (calcHeight (root->m_left), calcHeight (root->m_right));
    root->m_calcHeight = h;
    return h;
  }

  string dotNode (NodePtr node, int nodeNum)
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
  void toDot (const string& p_fileName, const T& label, NodePtr root)
  {
    fstream fout ;
    fout.open (p_fileName.c_str(), ios_base::out);
    fout << "digraph \"\" {" << endl;
    fout << "node [shape=plaintext];" << endl;
    fout << boost::format ("\tlabel=\"%1%\"") % label << endl;
    queue < pair <NodePtr, int> > nodes;
    nodes.push (make_pair (root, 0));

    int i(0);
    while (!nodes.empty())
    {
      pair<NodePtr, int>& node = nodes.front();
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

  int height (NodePtr node)
  {
    return node ? node->m_height : -1;
  }

  void traverseZigZagOrder (stack<NodePtr>& curStack, stack<NodePtr>& childStack, TraverseDirection d)
  {
    while (!curStack.empty())
    {
      NodePtr node = curStack.top();
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

  void traverseZigZagOrder (NodePtr root)
  {
    if (!root) {
      return;
    }

    stack <NodePtr> s;
    stack <NodePtr> cs;
    s.push (root);

    traverseZigZagOrder (s, cs, RightToLeft);
  }

  void traverseLevelOrder (NodePtr root)
  {
    if (!root) {
      return;
    }

    queue<NodePtr> q;
    q.push (root);

    while (!q.empty())
    {
      NodePtr node = q.front();

      if (node->m_left) {
        q.push (node->m_left);
      }

      if (node->m_right) {
        q.push (node->m_right);
      }

      q.pop();
    }
  }

  void singleRotateChild (Direction d, NodeRef k2)
  {
    NodePtr k1;
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

  void doubleRotateChild (Direction d, NodeRef root)
  {
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

  void print (NodePtr root)
  {
    if (!root) {
      return;
    }

    print (root->m_left);
    print (root->m_right);
  }
  
  int size (NodePtr root)
  {
    int sum (0);

    if (!root) {
      return 0;
    }

    sum = 1 + size (root->m_left) + size (root->m_right); 
    return sum;
  }

  void insert (NodeRef root, int val, NodePtr p_root)
  {
    if (!root) {
      root = new Node (val);
    } else if (val < root->m_val) {
      insert (root->m_left, val, p_root);
      if (height (root->m_left) - height(root->m_right) == 2) {
        if (val < root->m_left->m_val) {
          singleRotateChild (Left, root);
        } else {
          doubleRotateChild (Left, root);
        }
      }
    } else if (val > root->m_val) {
      insert (root->m_right, val, p_root);
      if (height (root->m_right) - height(root->m_left) == 2) {
        if (val > root->m_right->m_val) {
          singleRotateChild (Right, root);
        } else {
          doubleRotateChild (Right, root);
        }
      }
    } else {
      return;
    }
    root->m_height = max(height(root->m_left), height (root->m_right)) + 1;
  }

  bool find (NodePtr root, int val)
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
    m_root = new Node(p_val);
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

void avl::print (const string& p_label) const
{
  if (!m_root) {
    return ;
  }

  calcHeight(m_root);

  fileNum++;
  ::toDot ((fileNameFmt % fileNum).str(), p_label, m_root);
}

void avl::traverse (TraverseType t) const
{
  switch (t)
  {
    case InOrder:
      //print();
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

void avl::remove (int val)
{
  if (!m_root) {
    return;
  }
}
