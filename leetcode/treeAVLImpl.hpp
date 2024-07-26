#include <iostream>
#include "../include/header.hpp"


int max(int a, int b)
{
  return (a > b) ? a : b;
}


namespace balanced_trees
{
template <typename V>
class NodeAVL
{
 public:
  V key;
  NodeAVL<V>* left;
  NodeAVL<V>* right;
  int height;
};


template <typename V>
class TreeAVL
{
 public:
  int height(NodeAVL<V>* N)
  {
    if (N == NULL)
      return 0;
    return N->height;
  }

  NodeAVL<V><V>* newNode(int key)
  {
    NodeAVL<V>* node = new NodeAVL<V>();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
  }

  NodeAVL<V>* rightRotate(NodeAVL<V>* y)
  {
    NodeAVL<V>* x = y->left;
    NodeAVL<V>* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
  }

  NodeAVL<V>* leftRotate(NodeAVL<V>* x)
  {
    NodeAVL<V>* y = x->right;
    NodeAVL<V>* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
  }

  int getBalanceFactor(NodeAVL<V>* N)
  {
    if (N == NULL)
      return 0;
    return height(N->left) - height(N->right);
  }

  NodeAVL<V>* insertNode(NodeAVL<V>* node, int key)
  {
    if (node == NULL)
      return (newNode(key));
    if (key < node->key)
      node->left = insertNode(node->left, key);
    else if (key > node->key)
      node->right = insertNode(node->right, key);
    else
      return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1) {
      if (key < node->left->key) {
        return rightRotate(node);
      }
      else if (key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
      }
    }
    if (balanceFactor < -1) {
      if (key > node->right->key) {
        return leftRotate(node);
      }
      else if (key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
      }
    }
    return node;
  }

  NodeAVL<V>* nodeWithMinimumValue(NodeAVL<V>* node)
  {
    NodeAVL<V>* current = node;
    while (current->left != NULL)
      current = current->left;
    return current;
  }

  NodeAVL<V>* deleteNode(NodeAVL<V>* root, int key)
  {
    if (root == NULL)
      return root;
    if (key < root->key)
      root->left = deleteNode(root->left, key);
    else if (key > root->key)
      root->right = deleteNode(root->right, key);
    else {
      if ((root->left == NULL) || (root->right == NULL)) {
        NodeAVL<V>* temp = root->left ? root->left : root->right;
        if (temp == NULL) {
          temp = root;
          root = NULL;
        }
        else
          *root = *temp;
        free(temp);
      }
      else {
        NodeAVL<V>* temp = nodeWithMinimumValue(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
      }
    }

    if (root == NULL)
      return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balanceFactor = getBalanceFactor(root);
    if (balanceFactor > 1) {
      if (getBalanceFactor(root->left) >= 0) {
        return rightRotate(root);
      }
      else {
        root->left = leftRotate(root->left);
        return rightRotate(root);
      }
    }
    if (balanceFactor < -1) {
      if (getBalanceFactor(root->right) <= 0) {
        return leftRotate(root);
      }
      else {
        root->right = rightRotate(root->right);
        return leftRotate(root);
      }
    }
    return root;
  }

  void printTree(NodeAVL<V>* root, std::string indent, bool last)
  {
    if (root != nullptr) {
      std::cout << indent;
      if (last) {
        std::cout << "R----";
        indent += "   ";
      }
      else {
        std::cout << "L----";
        indent += "|  ";
      }
      std::cout << root->key << std::endl;
      printTree(root->left, indent, false);
      printTree(root->right, indent, true);
    }
  }
}; // class TreeAVL
} // namespace balanced_trees