#include <binary_tree.hpp>

typedef bst::node* Node;

namespace {

  void toLinkedList (Node root, Node& prev, Node& head)
  {
    if (!root) {
      return ;
    }

    toLinkedList (root->left, prev, head);
    root->left = prev;

    if (prev) {
      prev->right = root;
    } else {
      head = root;
    }

    Node right (root->right);

    head->left = root;
    root->right = head;

    toLinkedList (right, prev, head);
  }

  void traverseLevelOrder (bst::node* root)
  {
    if (!root) {
      return;
    }

    queue<bst::node*> q;
    q.push (root);

    while (!q.empty())
    {
      bst::node* node = q.front();

      if (node->left) {
        q.push (node->left);
      }

      if (node->right) {
        q.push (node->right);
      }

      cout << node->m_value << endl;

      q.pop();
    }
  }

  int sumNodes (Node n)
  {
    if (!n)
      return 0;

    int sum(0);
    sum += n->m_value;
    sum += sumNodes (n->left);
    sum += sumNodes (n->right);

    return sum;
  }

  void modifyRoot (Node root)
  {
  }

  bst::node* findMin (bst::node*& root)
  {
    if (!root) {
      return 0;
    } else if (!root->left) {
      return root;
    } else {
      findMin (root->left);
    }
  }
}

bst::bst()
  :m_root (0)
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

bool bst::find (int val, Node root)
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

void bst::printTree(Node root)
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
  Node cur;
  for (cur = m_root; cur && cur->left; cur = cur->left);
  return cur->m_value;
}

int bst::findMax()
{
  Node cur;
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

void bst::remove (int val, Node& root)
{
  if (!root) {
    return;
  }

  if (val < root->m_value) {
    remove (val, root->left);
  } else if (val > root->m_value) {
    remove (val, root->right);
  } else if (root->left && root->right){
    root->m_value = ::findMin (root->right)->m_value;
    remove (root->m_value, root->right);
  } else {
    Node old = root;
    root = root->left ? root->left : root->right;
    delete old;
  }
}

int bst::height ()
{
  return height (m_root);
}

int bst::height(Node root)
{
  if (!root)
    return 0;

  return 1 + max(height(root->left), height(root->right));
}

bool bst::isBalanced()
{
  return isBalanced(m_root);
}

bool bst::isBalanced (Node root)
{
  if (!root)
  {
    return true;
  }

  int hl = height(root->left);
  int hr = height(root->right);

  cout << '(' << hl << ',' << hr << ')' << endl;

  if ((abs (hl - hr) <= 1) && isBalanced (root->left) && isBalanced (root->right))
    return true;
  return false;
}

int bst::findMin (Node root, int k)
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

int bst::numChildren(Node root)
{
  if (!root) {
    return 0;
  }

  return (1 + numChildren(root->left) + numChildren(root->right));
}

bool bst::isMirrorImage (Node leftNode, Node rightNode)
{
  if (!leftNode && !rightNode)
    return true ;
  else if (leftNode && rightNode)
  {
    return isMirrorImage (leftNode->left, rightNode->right) &&
           isMirrorImage (leftNode->right, rightNode->left)
           ;
  }
  else
    return false;
}

void bst::traverseZigZag (Node root, Direction d)
{
  stack<Node>& curStack = (d == LeftToRight) ? l2r : r2l; 
  stack<Node>& childrenStack = (d == LeftToRight) ? r2l : l2r;

  while (!curStack.empty())
  {
    Node n = curStack.top();
    cout << n->m_value << endl;
    switch (d)
    {
      case LeftToRight:
        if (n->left)
          childrenStack.push (n->left);
        if (n->right)
          childrenStack.push (n->right);
        break;
      case RightToLeft:
        if (n->right)
          childrenStack.push (n->right);
        if (n->left)
          childrenStack.push (n->left);
        break;
      default:
        break;
    }
    curStack.pop();
  }

  while (!childrenStack.empty())
  {
    Direction newDir = (d == LeftToRight) ? RightToLeft : LeftToRight;
    traverseZigZag (childrenStack.top(), newDir);
  }
}

void bst::traverseLevel (Node root)
{
}

Node bst::commonAncestor (Node root, int p,  int q)
{
  if (!root)
    return 0;

  if (root->m_value == p || root->m_value == q) {
    return root;
  }

  Node l = commonAncestor (root->left, p, q);
  Node r = commonAncestor (root->right, p, q);

  if (l && r)
  {
    return root;
  }
  else if (l)
    return l;
  else if (r)
    return r;
  return (Node)0;
}

void bst::morrisTraverse (Node root)
{
  Node p;
  Node pre;

  if (!root) 
    return;

  for (p = root; p != 0;)
  {
    if (!p->left)
    {
      cout << p->m_value << ',';
      p = p->right;
      continue; 
    }

    for (pre = p->left; pre->right != 0 && pre->right != p; pre = pre->right);

    if (!pre->right)
    {
      pre->right = p;
      p = p->left; 
      continue;
    }
    else
    {
      pre->right = 0;
      cout << p->m_value << ',';
      p = p->right;
      continue;
    }
  }

  cout << endl;
}

void bst::sumLeftRight (Node root)
{
  if (!root) {
    return;
  }

  int sum(0);
  if (!root->left && !root->right) {
    root->m_value = 0;
  }

  else {
    sum += sumNodes (root->left);
    sum += sumNodes (root->right);
    root->m_value = sum;
  }
  sumLeftRight (root->left);
  sumLeftRight (root->right);
}

void bst::toLinkedList ()
{
  if (!m_root) {
    return;
  }

  Node prev(0), head(0);
  ::toLinkedList (m_root, prev, head);

  Node fast(head), slow(head);

  while (fast && slow)
  {
    cout << slow->m_value << endl;

    if (fast->right) {
      fast = fast->right->right;
    }
    slow = slow->right;

    if (fast == slow) {
      break;
    }
  }
}

void bst::printToDot (const string& p_fileName) const
{

  if (!m_root) {
    return;
  }

  queue < pair<Node, int> > nodes;
  nodes.push (make_pair(m_root, 0));

  fstream fout ;
  fout.open (p_fileName.c_str(), ios_base::out);

  fout << "digraph \"\" {" << endl;
  fout << "node [shape=\"record\" height=0.05];" << endl;

  int i (0);
  while (!nodes.empty()) {
    pair <Node, int>& current = nodes.front();
    Node& curNode = current.first;
    int parentNum (current.second);

    fout << fmt ("node%1%[label=\"<f0>|<f1>%2%|<f2>\"];") 
      % parentNum
      % curNode->m_value 
      << endl;

    if (curNode->left) {
      nodes.push (make_pair(curNode->left, ++i)) ;
      fout << fmt ("\"node%1%\":f0 -> \"node%2%\":f1;")
        % parentNum % i << endl;
    }

    if (curNode->right) {
      nodes.push (make_pair(curNode->right, ++i));
      fout << fmt ("\"node%1%\":f2 -> \"node%2%\":f1;")
        % parentNum % i << endl;
    }

    nodes.pop();
  }

  fout << "}";
  fout.close();
}

void bst::printSiblingNodes (int val)
{
  if (!m_root) {
    return;
  }

  Node n, p;

  n = m_root;
  p = m_root;

  if (val == m_root) {
    return;
  }
}
