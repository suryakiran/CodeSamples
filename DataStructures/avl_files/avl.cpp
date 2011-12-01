#include <avl.hpp>

struct avl_node
{
  avl_node* m_left;
  avl_node* m_right;
  avl_node* m_parent;

  int m_height;
  int m_val;

  avl_node(int p_val)
    : m_left(0), m_right(0), m_parent(0),
      m_height(0), m_val(p_val)
  {
  }
};

namespace {

  int height (avl_node* root)
  {
    if (!root) {
      return 0;
    }

    return 1 + max(height(root->m_left), height(root->m_right));
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

  void insert (avl_node* root, int val)
  {
    if (!root) {
      root = new avl_node (val);
    }

    if (root->m_val == val) {
      return;
    } else if (val < root->m_val) {
      if (root->m_left) {
        insert (root->m_left, val);
      } else {
        avl_node* node = new avl_node (val);
        root->m_left = node;
        node->m_parent = root;
      }
    } else {
      if (root->m_right) {
        insert (root->m_right, val);
      } else {
        avl_node* node = new avl_node (val);
        root->m_right = node;
        node->m_parent = root;
      }
    }
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
    ::insert (m_root, p_val);
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
