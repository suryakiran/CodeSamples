#include <splay.hpp>
#include <limits>

typedef enum {
  Left = 0,
  Right,
} Direction;

struct splay_node
{
  splay_node (int p_val)
    :m_val(p_val), m_left(0), m_right(0)
  {
  }

  int m_val;
  Node m_left;
  Node m_right;
  Node m_parent;
};

namespace {

  pair<int, Node> findMin (Node root)
  {
    Node r;
    for (r = root; r->m_left; r = r->m_left);
    return make_pair (r->m_val, r);
  }

  pair<int, Node> findMax (Node root)
  {
    Node r;
    for (r = root; r->m_right; r = r->m_right);
    return make_pair (r->m_val, r);
  }

  template <class NodeType>
    void splayNode (
        Direction d,
        NodeType p_node,
        typename boost::add_reference<NodeType>::type p_root
        )
    {
      typedef NodeType _NodePtr;
      typedef typename boost::remove_pointer <NodeType>::type _Node;

      bool leftChild (true);
      bool changeRoot (false);

      _NodePtr parent = p_node->m_parent;
      _NodePtr rightPtr = p_node->m_right;
      _NodePtr leftPtr = p_node->m_left;
      _NodePtr grandParent = parent->m_parent;

      if (grandParent == p_root) {
        changeRoot = true;
      }

      if (grandParent) {
        if (parent == grandParent->m_right) {
          leftChild = false;
        }
      }

      switch (d)
      {
        case Left:
          p_node->m_parent = parent->m_parent;
          p_node->m_left = parent;

          if (leftPtr) {
            leftPtr->m_parent = parent;
          }

          parent->m_right = leftPtr;
          parent->m_parent = p_node;
          p_node->m_parent = grandParent;
          break;
        case Right:
          p_node->m_parent = parent->m_parent;
          p_node->m_right = parent;

          if (rightPtr) {
            rightPtr->m_parent = parent;
          }

          parent->m_left = rightPtr;
          parent->m_parent = p_node;
          p_node->m_parent = grandParent;
          break;
        default:
          break;
      }

      if (grandParent) {
        if (leftChild) {
          grandParent->m_left = p_node;
        } else {
          grandParent->m_right = p_node;
        }
        if (changeRoot) {
          p_root = grandParent;
        }
      } else {
        p_root = p_node;
      }
    }

  template <class NodeType>
    NodeType
    insert (
        const int& p_val, 
        typename boost::add_reference<NodeType>::type p_root, 
        typename boost::add_reference<NodeType>::type p_parent
        )
    {
      typedef typename boost::remove_pointer<NodeType>::type _Node;
      if (!p_root) {
        p_root = new _Node (p_val);
        p_root->m_parent = p_parent;
        return p_root;
      }

      else if (p_val < p_root->m_val) {
        return insert<NodeType> (p_val, p_root->m_left, p_root);
      }

      else if (p_val > p_root->m_val) {
        return insert<NodeType> (p_val, p_root->m_right, p_root);
      }
    }

  struct toString
  {
    template <class T>
    string operator() (const T& p_os) {
      return p_os.str();
    }

    string operator() (const string& p_s) {
      return p_s;
    }

    string operator() (const char* p_s) {
      return string(p_s);
    }
  };

  template <class NodeType>
  string dotBinaryNode (NodeType node, int nodeNum)
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

  template <class StringType, class LabelType, class NodeType>
  void toDot (const StringType& p_fileName, const LabelType& p_label, const NodeType& p_root,
      size_t p_numItems)
  {
    fstream fout ;
    fout.open (toString()(p_fileName).c_str(), ios_base::out);
    fout << "digraph {" << endl;
    fout << "\tnode [shape=plaintext];" << endl;
    fout << boost::format ("\tlabel=\"%1%\"") % p_label << endl;

    queue < pair<NodeType, size_t> >  nodes;

    size_t i(0);
    nodes.push (make_pair (p_root, 0));
    while (!nodes.empty())
    {
      pair<NodeType, size_t>& node = nodes.front();
      fout << dotBinaryNode (node.first, node.second);

      if (node.first->m_left) {
        nodes.push (make_pair (node.first->m_left, ++i));
        fout << boost::format ("node%1%:left->node%2%:center") 
          % node.second % i << endl;
      }

      if (node.first->m_right) {
        nodes.push (make_pair (node.first->m_right, ++i));
        fout << boost::format ("node%1%:right->node%2%:center") 
          % node.second % i << endl;
      }

      if (i > p_numItems + 1) {
        cout << "***** ERROR: Bailing Out *****" << endl;
        break;
      }

      nodes.pop();
    }
    fout << "}";
    fout.close();
  }
}

splay::splay()
  :m_root(0), m_null(0), m_fileNum (0), m_numItems(0)
{
}

splay::~splay()
{
}

splay& splay::insert (int val)
{
  Node node = ::insert<Node> (val, m_root, m_null);
  splayNode (node);
  ++m_numItems;
  return *this;
}

bool splay::find (int val)
{
  return find (val, m_root, m_null);
}

bool splay::find (int val, NodeRef root, NodeRef parent)
{
  if (!root) {
    if (parent) {
      splayNode (parent);
    }
    return false;
  }

  if (val < root->m_val) {
    return find(val, root->m_left, root);
  } else if (val > root->m_val) {
    return find (val, root->m_right, root) ;
  }

  else 
  {
    splayNode (root);
    return true;
  }
}

void splay::print (const string& p_label)
{
  if (!m_root) {
    return;
  }

  m_fileNum++;
  toDot (boost::format ("splay-%1%.gv") % m_fileNum, p_label, m_root, m_numItems);
}

void splay::printTree(Node root)
{
}

pair<int, Node> splay::findMin()
{
  return ::findMin (m_root);
}

pair<int, Node> splay::findMax()
{
  return ::findMax (m_root);
}

bool splay::remove (int val)
{
  pair <bool, Node> r = remove(val, m_root, m_null);

  if (r.second) {
    splayNode (r.second);
  }

  return r.first;
}

pair<int, int>
splay::range (int val)
{
  pair<int, int> r;
  r.first = numeric_limits<int>::min();
  r.second = numeric_limits<int>::max();

  return r;
}

pair <bool, Node>
splay::remove (int val, Node root, Node parent)
{
  if (!root) {
    return make_pair (false, parent);
  }

  if (val < root->m_val) {
    return remove (val, root->m_left, root);
  } else if (val > root->m_val) {
    return remove (val, root->m_right, root);
  }

  else {
    if (root->m_left && root->m_right) {
      pair<int, Node> min = ::findMin (root->m_right);
      root->m_val = min.first;
      remove (root->m_val, root->m_right, root);
      return make_pair(true, parent);
    } else if (root->m_left) {
      if (parent->m_left == root) {
        parent->m_left = root->m_left;
      } else {
        parent->m_right = root->m_left;
      }
      return make_pair (true, parent);
    } else if (root->m_right) {
      if (parent->m_left == root) {
        parent->m_left = root->m_right;
      } else {
        parent->m_right = root->m_right;
      }
      return make_pair (true, parent);
    } else {
      if (parent->m_left == root) {
        parent->m_left = NULL;
      } else {
        parent->m_right = NULL;
      }
      return make_pair (true, parent);
    }
    delete root;
  }
}

void splay::splayNode (Node p_node)
{
  if (p_node == m_root) {
    return;
  }

  Node parent (p_node->m_parent);

  if (parent == m_root) {
    if (p_node == m_root->m_left) {
      ::splayNode<Node> (Right, p_node, m_root);
    } else {
      ::splayNode<Node> (Left, p_node, m_root);
    }
  } else {
    Node grandParent = parent->m_parent;

    if (grandParent->m_left == parent) {
      if (p_node == parent->m_left) {
        ::splayNode <Node> (Right, p_node, m_root);
        ::splayNode <Node> (Right, p_node, m_root);
      } else { 
        ::splayNode <Node> (Left, p_node, m_root);
        ::splayNode <Node> (Right, p_node, m_root);
      }
    } else {
      if (p_node == parent->m_right) {
        ::splayNode <Node> (Left, p_node, m_root);
        ::splayNode <Node> (Left, p_node, m_root);
      } else { 
        ::splayNode <Node> (Right, p_node, m_root);
        ::splayNode <Node> (Left, p_node, m_root);
      }
    }
  }
  splayNode (p_node);
}

#if 0
bool splay::splayNode (Node node)
{
  if (node == m_root) {
    return false;
  }

  Node parent (node->m_parent);
  Node grandParent (parent->m_parent);

  if (parent == m_root) { //node is child of root
    if (node == m_root->m_left) {
      m_root = ::splayNode(Right, node, m_root);
    }
    else {
      m_root = ::splayNode(Left, node, m_root);
    }
  }
  else if (node == parent->m_left) {
    if (parent == grandParent->m_left) { // node is left child of left child
      m_root = ::splayNode (Right, node, m_root);
      //print ((boost::format ("Zig: %1%") % node->m_val).str());
      m_root = ::splayNode (Right, node, m_root);
      //print ((boost::format ("Zig: %1%") % node->m_val).str());
      //if (node) {
      //  cout << node->m_val << endl;
      //}
    }
    else { // node is left child of right child
      m_root = ::splayNode (Right, node, m_root);
    }
  }
  else {
    if (parent == grandParent->m_right) { // node is right child of right child
      m_root = ::splayNode (Left, node, m_root);
      m_root = ::splayNode (Left, node, m_root);
    }
    else { // node is right child of left child
      m_root = ::splayNode (Left, node, m_root);
    }
  }

  splayNode (node);
}
#endif
