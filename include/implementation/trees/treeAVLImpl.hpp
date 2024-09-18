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
    auto leftHeight = (left() ? left()->getHeight() : 0);
    auto rightHeight = (right() ? right()->getHeight() : 0);
    Node<KeyType>::setHeight(1 + std::max(leftHeight, rightHeight));
    Node<KeyType>::setBalance(leftHeight - rightHeight);
  }

  NodeType* left() { return static_cast<NodeType*>(Base::m_edges[0]); }
  NodeType* right() { return static_cast<NodeType*>(Base::m_edges[1]); }

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
  using BaseNode = Node<KeyType>;

 public:
  AVLTree(const KeyType& key) : BasicTree<KeyType>(2, new NodeType(key)){};
  AVLTree(NodeType* node) : BasicTree<KeyType>(2, node){};
  ~AVLTree() = default;

  NodeType* getNode(const KeyType& key)
  {
    return static_cast<NodeType*>(Base::getNode(key));
  }

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
    if (!root)
      return nullptr;

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
    if (!root)
      return nullptr;

    NodeType* y = root->right();
    NodeType* x = y->left();

    y->putLeft(root);
    root->putRight(x);
    root->updateHeight();
    y->updateHeight();
    return y;
  }

  NodeType* removeNode(NodeType* root, NodeType* node)
  {
    if (!root)
      return nullptr;
    if (!node || !Base::m_map->hasVertex(node))
      return nullptr;

    if (node->key() < root->key())
      root->putLeft(removeNode(root->left(), node));
    else if (node->key() > root->key())
      root->putRight(removeNode(root->right(), node));
    else {
      if (!root->left() || !root->right()) {
        NodeType* tmp = (root->left() ? root->left() : root->right());
        if (!tmp)
          tmp = root;
        else
          *root = *tmp;
      }
      else {
        NodeType* tmp = (NodeType*)(Base::minValueNode(root->right()));
        root->key() = tmp->key();
        root->putRight(removeNode(root->right(), tmp));
      }
    }

    if (!root)
      return nullptr;

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