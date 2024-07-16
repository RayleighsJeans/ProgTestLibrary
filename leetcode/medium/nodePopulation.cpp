#include "../../include/header.hpp"


using namespace helper;


// Definition for a Node.
class Node
{
 public:
  int val;
  Node* left;
  Node* right;
  Node* next;

  Node() : val(0), left(NULL), right(NULL), next(NULL){};

  Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL){};

  Node(int _val, Node* _left, Node* _right, Node* _next)
      : val(_val), left(_left), right(_right), next(_next){};

  void traverse(int i = 0)
  {
    if (i > 0)
      std::cout << std::endl;
    for (int j = 0; j < i; j++)
      std::cout << "\t";

    std::cout << " (lvl:" << i;
    std::cout << "-val:" << val << ")";
    if (next) {
      std::cout << "-next (val:" << next->val << ")";
    }
    if (left) {
      std::cout << " -- left";
      left->traverse(i + 1);
    }
    if (right) {
      std::cout << " -- right";
      right->traverse(i + 1);
    }
    if (!right && !left && !next)
      std::cout << std::endl;
  };
}; // class Node


class Solution
{
 public:
  Node* connect(Node* root)
  {
    if (!root)
      return nullptr;
    if (root->left) { // right node exists (perfect tree)
      root->left->next = root->right;
    }
    if (root->left && root->next) { // right root node exists?
      root->right->next = root->next->left;
    }
    connect(root->left);
    connect(root->right);
    return root;
  } // connect
};  // class Solution


int main()
{
  Node* root = new Node(1, new Node(2, new Node(4), new Node(5), nullptr),
                        new Node(3, new Node(6), new Node(7), nullptr),
                        nullptr); // [1, 2, 3, 4, 5, 6, 7]

  Solution S;
  root = S.connect(root);

  root->traverse(0);
  return 0;
}; // main