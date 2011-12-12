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
  splay_node* m_left;
  splay_node* m_right;
  splay_node* m_parent;
};

namespace {

  splay_node* splayNode (Direction d, splay_node* node, splay_node* root)
  {
    splay_node* parent (node->m_parent);
    splay_node* grandparent (parent->m_parent);
    splay_node* leftChild (node->m_left);
    splay_node* rightChild (node->m_right);
    switch (d)
    {
      case Right:
        parent->m_left = rightChild;
        node->m_right = parent;
        if (grandparent) {
          if (parent == grandparent->m_right) {
            grandparent->m_right = node;
          } else {
            grandparent->m_left = node;
          }
        }
        node->m_parent = grandparent;
        parent->m_parent = node;
        if (rightChild) {
          rightChild->m_parent = parent;
        }
        break;
      case Left:
        parent->m_right = leftChild;
        node->m_left = parent;
        if (grandparent) {
          if (parent == grandparent->m_left) {
            grandparent->m_left = node;
          } else {
            grandparent->m_right = node;
          }
        }
        node->m_parent = grandparent;
        parent->m_parent = node;
        if (leftChild) {
          leftChild->m_parent = parent;
        }
        break;
      default:
        break;
    }

    if (parent == root) {
      return node;
    } else {
      return root;
    }
  }

  template <class NodeType>
  NodeType*& insert (const int& p_val, NodeType*& p_root, NodeType*& p_parent)
  {
    if (!p_root) {
      p_root = new NodeType(p_val);
      p_root->m_parent = p_parent;
      return p_root;
    }

    else if (p_val < p_root->m_val) {
      return insert (p_val, p_root->m_left, p_root);
    }

    else if (p_val > p_root->m_val) {
      return insert (p_val, p_root->m_right, p_root);
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
  void toDot (const StringType& p_fileName, const LabelType& p_label, const NodeType& p_root)
  {
    fstream fout ;
    fout.open (toString()(p_fileName).c_str(), ios_base::out);
    fout << "digraph {" << endl;
    fout << "\tnode [shape=plaintext];" << endl;
    fout << boost::format ("\tlabel=\"%1%\"") % p_label << endl;

    queue < pair<NodeType, int> >  nodes;

    int i(0);
    nodes.push (make_pair (p_root, 0));
    while (!nodes.empty())
    {
      pair<NodeType, int>& node = nodes.front();
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

      nodes.pop();
    }
    fout << "}";
    fout.close();
  }
}

splay::splay()
  :m_root(0), m_null(0), m_fileNum (0)
{
}

splay::~splay()
{
}

splay& splay::insert (int val)
{
  ::insert (val, m_root, m_null);
  return *this;
}

bool splay::find (int val)
{
  return find (val, m_root);
}

bool splay::find (int val, splay_node*& root)
{
  if (!root) {
    return false;
  }

  if (val < root->m_val) {
    return find(val, root->m_left);
  } else if (val > root->m_val) {
    return find (val, root->m_right) ;
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
  toDot (boost::format ("splay-%1%.gv") % m_fileNum, p_label, m_root);
}

void splay::printTree(splay_node* root)
{
}

int splay::findMin()
{
}

int splay::findMax()
{
}

void splay::remove (int val)
{
}

pair<int, int>
splay::range (int val)
{
  pair<int, int> r;
  r.first = numeric_limits<int>::min();
  r.second = numeric_limits<int>::max();

  return r;
}

void splay::remove (int val, splay_node* root)
{
}

bool splay::splayNode (splay_node* node)
{
  if (node == m_root) {
    return false;
  }

  splay_node* parent (node->m_parent);
  splay_node* grandParent (parent->m_parent);

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
