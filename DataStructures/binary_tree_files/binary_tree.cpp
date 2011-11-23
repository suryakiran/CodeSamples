#include <binary_tree.hpp>
#include <limits>

bst::bst()
{
}

bst::~bst()
{
}

bst& bst::insert (int val)
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

bool bst::find (int val)
{
  return find (val, m_root);
}

bool bst::find (int val, node* root)
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

void bst::print ()
{
  cout << "Root: " << m_root->m_value << endl;
  printTree (m_root);
  cout << endl;
}

void bst::printTree(node* root)
{
  if (!root) {
    return ;
  }

  printTree (root->left);
  cout << root->m_value << ", ";
  printTree (root->right);
}

int bst::findMin()
{
  node* cur;
  for (cur = m_root; cur && cur->left; cur = cur->left);
  return cur->m_value;
}

int bst::findMax()
{
  node* cur;
  for (cur = m_root; cur && cur->right; cur = cur->right);
  return cur->m_value;
}

void bst::remove (int val)
{
  remove (val, m_root);
}

pair<int, int>
bst::range (int val)
{
  pair<int, int> r;
  r.first = numeric_limits<int>::min();
  r.second = numeric_limits<int>::max();
}

void bst::remove (int val, node* root)
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

int bst::findMin (node* root, int k)
{
  int n (numChildren (root->left));
  cout << "N: " << n << endl;

  if (n == k-1) {
    return root->m_value;
  } else if (n >= k) {
    return findMin (root->left, k);
  } else {
    return findMin (root->right, k - n - 1);
  }
}

int bst::findMin(int k)
{
  return (findMin (m_root, k));
}

int bst::numChildren(node* root)
{
  if (!root) {
    return 0;
  }

  return (1 + numChildren(root->left) + numChildren(root->right));
}
