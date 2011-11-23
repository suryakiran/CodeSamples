#include <splay.hpp>
#include <limits>

splay::splay()
{
}

splay::~splay()
{
}

splay& splay::insert (int val)
{
  if (!m_root) 
  {
    m_root = new node (val);
  }

  else 
  {
    if (!find (val))
    {
      node *cur = new node (val);
      if (val > m_lastVisited->m_value)
        m_lastVisited->right = cur;
      else
        m_lastVisited->left = cur;
    }
  }

  return *this;
}

bool splay::find (int val)
{
  return find (val, m_root);
}

bool splay::find (int val, node* root)
{
  if (!root)
    return false;

  m_lastVisited = root;

  if (root->m_value == val)
    return true ;
  else if (val > root->m_value)
    return find (val, root->right);
  else if (val < root->m_value)
    return find(val, root->left);
}

void splay::print ()
{
  cout << "Root: " << m_root->m_value << endl;
  printTree (m_root);
  cout << endl;
}

void splay::printTree(node* root)
{
  if (!root) {
    return ;
  }

  printTree (root->left);
  cout << root->m_value << ", ";
  printTree (root->right);
}

int splay::findMin()
{
  node* cur;
  for (cur = m_root; cur && cur->left; cur = cur->left);
  return cur->m_value;
}

int splay::findMax()
{
  node* cur;
  for (cur = m_root; cur && cur->right; cur = cur->right);
  return cur->m_value;
}

void splay::remove (int val)
{
  remove (val, m_root);
}

pair<int, int>
splay::range (int val)
{
  pair<int, int> r;
  r.first = numeric_limits<int>::min();
  r.second = numeric_limits<int>::max();
}

void splay::remove (int val, node* root)
{
  if (!root) {
    return;
  }

  if (root->m_value == val) {
    if (root->left && root->right) 
    {
      node* cur;
      node* parent;
      for (cur = root->right; cur && cur->left; parent = cur, cur = cur->left);
      root->m_value = cur->m_value;
      delete cur;
      parent->left = NULL;
    }
    else 
    {
      node* child = NULL;
      if (root->left || root->right)
        child = root->left ? root->left : root->right;
      if (val < m_lastVisited->m_value) 
        m_lastVisited->left = child;
      else 
        m_lastVisited->right = child;
      delete root;
    }
  }
  else if (val < root->m_value) {
    m_lastVisited = root;
    remove (val, root->left);
  } else  {
    m_lastVisited = root;
    remove (val, root->right);
  }
}

void splay::rotateRight(node* current)
{
  node* tmp = m_root;
}

void splay::rotateLeft (node* current)
{
  current->parent->left = current->right; 
  current->right = current->parent;
  current->parent->parent = current;
}
