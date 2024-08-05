#pragma once


#include "basicTreeImpl.hpp"


namespace trees
{
namespace binary
{
template <typename KeyType>
class BinaryNode : public Node<KeyType>
{
 private:
  using NodeType = BinaryNode<KeyType>;
  using Base = Node<KeyType>;

 public:
  BinaryNode(KeyType key) : Node<KeyType>(key, 2){};
  ~BinaryNode() = default;

  void updateHeight()
  {
    Node<KeyType>::setHeight(
      1 + std::max(left()->getHeight(), right()->getHeight()));
    Node<KeyType>::setBalance(left()->getHeight() - right()->getHeight());
  }

  NodeType* left() { return Base::m_edges[0]; }
  NodeType* right() { return Base::m_edges[1]; }

  void putLeft(NodeType* node) { Base::m_edges[0] = node; }
  void putRight(NodeType* node) { Base::m_edges[1] = node; }
};

namespace balanced
{
template <typename KeyType>
class AVLTree : public BasicTree<KeyType>
{
 private:
  using NodeType = BinaryNode<KeyType>;
  using Base = BasicTree<KeyType>;

 public:
  AVLTree(const KeyType& key) : BasicTree<KeyType>(2, new NodeType(key)){};
  AVLTree(NodeType* node) : BasicTree<KeyType>(2, node){};
  ~AVLTree() = default;

  NodeType* insertNode(NodeType* root, NodeType* node)
  {
    if (!root)
      return nullptr;

    if (node->key() < root->key())
      root->putLeft(insertNode(root->left(), node));
    else if (node->key() > root->key())
      root->putRight(insertNode(root->right(), node));
    else
      return node;

    root->setHeight(
      1 + std::max(root->left()->getHeight(), root->right()->getHeight()));

    root->updateHeight();
    if (root->getBalance() > 1) {
      if (node->key() < root->left()->key()) {
        return rightRotate(root);
      }
      else if (node->key() > root->left()->key()) {
        root->putLeft(leftRotate(node->left()));
        return rightRotate(root);
      }
    }

    if (root->getBalance() < -1) {
      if (node->key() > root->right()->key()) {
        return leftRotate(root);
      }
      else if (node->key() < root->right()->key()) {
        root->putRight(rightRotate(node->right()));
        return leftRotate(root);
      }
    }
    return node;
  }

  NodeType* rightRotate(NodeType* root)
  {
    NodeType* x = root->left();
    NodeType* y = x->right();

    x->putRight(root);
    root->putLeft(y);
    root->updateHeight();
    x->updateHeight();
    return x;
  }

  NodeType* leftRotate(NodeType* root)
  {
    NodeType* y = root->right();
    NodeType* x = y->left();

    y->putLeft(x);
    root->putRight(x);
    root->updateHeight();
    y->updateHeight();
    return y;
  }

  NodeType* removeNode(NodeType* root, NodeType* node)
  {
    if (!node || !Base::m_map->hasVertex(node))
      return nullptr;

    if (node->key() < root->key())
      root->putLeft(removeNode(root, node->key()));
    else if (node->key() > root->key())
      root->putRight(removeNode(root, node->key()));
    else {
      if (!root->left() || !root->right()) {
        NodeType* tmp = root->left() ? root->left() : root->right();
        if (!tmp)
          tmp = root;
        else
          *root = *tmp;
        free(tmp);
      }
      else {
        NodeType* tmp = Base::minValueNode(root->right());
        root->key() = tmp->key();
        root->right() = removeNode(tmp->key);
      }
    }

    root->updateHeight();

    if (root->getBalance() > 1) {
      if (root->left()->getBalance() >= 0) {
        return rightRotate(root);
      }
      else {
        root->putLeft(leftRotate(root->left()));
        return rightRotate(root);
      }
    }
    if (root->getBalance() < -1) {
      if (root->right()->getBalance() <= 0) {
        return leftRotate(root);
      }
      else {
        root->putRight(rightRotate(root->right()));
        return leftRotate(root);
      }
    }
    return root;
  }
}; // class TreeAVL
} // namespace balanced
} // namespace binary
} // namespace trees