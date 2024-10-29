#pragma once

#include <assert.h>
#include <map>
#include <memory>
#include <optional>

#include "linkedListImpl.hpp"


namespace linked_lists
{
template <typename LabelType>
class LinkedList
{
 private:
  using L = LabelType;

 private:
  std::map<std::shared_ptr<Node<L>>, L> m_map;

  std::shared_ptr<Node<L>> m_head;
  std::shared_ptr<Node<L>> m_tail;

 protected:
  void head(std::shared_ptr<Node<L>> node)
  {
    if (node && node != m_head)
      if (m_head && (m_head.use_count() == 1))
        m_head.reset();
    m_head.swap(node);
  }

  void tail(std::shared_ptr<Node<L>> node)
  {
    if (node && node != m_tail)
      if (m_tail && (m_tail.use_count() == 1))
        m_tail.reset();
    m_tail.swap(node);
  }

  void add(std::shared_ptr<Node<L>> node)
  {
    assert("Node in list." && !m_map.count(node));
    assert("Neighbor is cyclical." && !m_map.count(node->next()));
    m_map[node] = node->label();
  }

  void remove(const std::shared_ptr<Node<L>>& node) { m_map.erase(node); }

 public:
  LinkedList(std::shared_ptr<Node<L>> node)
  {
    if (!node)
      return;
    add(node);

    std::shared_ptr<Node<L>> tmp(node);
    head(tmp);

    if (node->next()) {
      while (tmp->next()) {
        tmp = tmp->next();
        add(tmp);
      }
    }
    tail(tmp);
  };

  LinkedList(const L& label) : LinkedList(std::make_shared<Node<L>>(label)) {};

  LinkedList() : LinkedList(nullptr) {};

  ~LinkedList() = default;

  void push_front(std::shared_ptr<Node<L>> node)
  {
    if (!node || (node == m_head))
      return;

    add(node);
    std::shared_ptr<Node<L>> oldHead(m_head);
    head(node);

    while (node->next()) {
      node = node->next();
      add(node);
    }
    node->next(oldHead);
  }

  void push_front(const L value)
  {
    push_front(std::make_shared<Node<L>>(value));
  }

  void push_back(std::shared_ptr<Node<L>> node)
  {
    if (!node || (node == m_tail))
      return;

    if (!m_head) {
      push_front(node);
      tail(m_head);
      return;
    }

    add(node);
    m_tail->next(node);

    std::shared_ptr<Node<L>> newTail(node);
    while (newTail->next()) {
      newTail = newTail->next();
      add(newTail);
    }
    tail(newTail);
  }

  void push_back(const L value) { push_back(std::make_shared<Node<L>>(value)); }

  void insert(std::shared_ptr<Node<L>> node, const size_t position,
              const bool debug = true)
  {
    if (position > m_map.size()) {
      if (debug)
        std::cout << "Position out of range." << std::endl;
      return;
    }
    if (!position) {
      push_front(node);
      return;
    }
    if (position == m_map.size() - 1) {
      push_back(node);
      return;
    }

    add(node);
    std::shared_ptr<Node<L>> tmp(m_head);

    for (size_t i = 0; i < position - 1 && tmp; ++i)
      tmp = tmp->next();

    node->next(tmp->next());
    tmp->next(node);
  }

  void insert(const L& value, const size_t position, const bool debug = true)
  {
    insert(std::make_shared<Node<L>>(value), position, debug);
  }

  void pop_front()
  {
    if (!m_head)
      return;

    remove(m_head);
    std::shared_ptr<Node<L>> tmp(m_head);

    if (m_tail == m_head) {
      m_head.reset();
      m_tail.reset();
    }
    else {
      head(m_head->next());
    }
    tmp->next(nullptr);
  }

  void pop_back()
  {
    if (!m_head)
      return;

    remove(m_tail);
    if (m_tail == m_head) {
      head(nullptr);
      tail(nullptr);
    }
    else {
      std::shared_ptr<Node<L>> tmp(m_head);
      while (tmp->next()->next())
        tmp = tmp->next();

      tail(tmp);
      m_tail->next(nullptr);
    }
  }

  void erase(const size_t position, const bool debug = true)
  {
    if (position >= m_map.size()) {
      if (debug)
        std::cout << "Position out of range." << std::endl;
      return;
    }
    if (!position) {
      pop_front();
      return;
    }
    if (position == m_map.size() - 1) {
      pop_back();
      return;
    }

    std::shared_ptr<Node<L>> previousNode(m_head);
    for (size_t i = 0; i < position - 1 && previousNode; ++i)
      previousNode = previousNode->next();

    std::shared_ptr<Node<L>> nodeToDelete(previousNode->next());
    std::shared_ptr<Node<L>> followerNode(nodeToDelete->next());

    previousNode->next(nullptr);
    previousNode->next(followerNode);
    nodeToDelete->next(nullptr);
    remove(nodeToDelete);
  }

  void erase(std::shared_ptr<Node<L>> node) { erase(find(node), false); }

  void erase(const L& label) { erase(find(label), false); }

  size_t find(std::shared_ptr<Node<L>> node, const bool debug = true) const
  {
    size_t position = 0;
    std::shared_ptr<Node<L>> tmp(m_head);
    while (tmp && node != tmp) {
      position++;
      tmp = tmp->next();
    }

    if (debug && (position == m_map.size()))
      std::cout << "Node not in list." << std::endl;
    return position;
  }

  size_t find(const L& label, const bool debug = true) const
  {
    size_t position = 0;
    std::shared_ptr<Node<L>> node(m_head);
    while (node && label != node->label()) {
      position++;
      node = node->next();
    }

    if (debug && (position == m_map.size()))
      std::cout << "Key not in list." << std::endl;
    return position;
  }

  const std::shared_ptr<Node<L>>& front() const { return m_head; }

  const std::shared_ptr<Node<L>>& back() const { return m_tail; }

  std::shared_ptr<Node<L>> at(const size_t position) const
  {
    if (position >= m_map.size())
      return nullptr;
    std::shared_ptr<Node<L>> node(m_head);
    for (size_t i = 0; i < position && node; ++i)
      node = node->next();
    return node;
  }

  size_t size() const { return m_map.size(); }

  friend std::ostream& operator<<(std::ostream& stream,
                                  const LinkedList<L>& list)
  {
    Node<L>* tmp = list.front().get();
    stream << "[";
    while (tmp) {
      stream << *tmp;
      if (tmp->next()) {
        stream << ", ";
      }
      tmp = tmp->next().get();
    }
    stream << "]";
    return stream;
  }
};


template <typename LabelType, typename EdgeType>
class LinkedEdgeList : public LinkedList<LabelType>
{
 private:
  using L = LabelType;
  using E = EdgeType;

 public:
  LinkedEdgeList(std::shared_ptr<EdgeNode<L, E>> node)
      : LinkedList<L>::LinkedList(node) {};

  LinkedEdgeList(const L& label, const E& edge)
      : LinkedEdgeList(std::make_shared<EdgeNode<L, E>>(label, nullptr, edge)) {
        };

  LinkedEdgeList() : LinkedList<L>::LinkedList() {};

  void push_front(const L& value, const E& edge)
  {
    push_front(std::make_shared<EdgeNode<L, E>>(value, nullptr, edge));
  }

  void push_front(std::shared_ptr<EdgeNode<L, E>> node)
  {
    LinkedList<L>::push_front(node);
  }

  void push_back(const E& edge, const L& value)
  {
    push_back(edge, std::make_shared<EdgeNode<L, E>>(value));
  }

  void push_back(const E& edge, std::shared_ptr<EdgeNode<L, E>> node)
  {
    back()->edge(edge);
    LinkedList<L>::push_back(node);
  }

  void insert(const L& value, const E& edge, const size_t position)
  {
    insert(std::make_shared<EdgeNode<L, E>>(value, nullptr, edge), position);
  }

  void insert(std::shared_ptr<EdgeNode<L, E>> node, size_t position)
  {
    LinkedList<L>::insert(node, position);
  }

  void pop_back()
  {
    LinkedList<L>::pop_back();
    back()->edge(E());
  }

  std::shared_ptr<EdgeNode<L, E>> front() const
  {
    return std::static_pointer_cast<EdgeNode<L, E>>(LinkedList<L>::front());
  }

  std::shared_ptr<EdgeNode<L, E>> back() const
  {
    return std::static_pointer_cast<EdgeNode<L, E>>(LinkedList<L>::back());
  }

  std::shared_ptr<EdgeNode<L, E>> at(const size_t position) const
  {
    return std::static_pointer_cast<EdgeNode<L, E>>(
      LinkedList<L>::at(position));
  }

  std::optional<E> edgeTo(std::shared_ptr<EdgeNode<L, E>> toNode) const
  {
    std::shared_ptr<EdgeNode<L, E>> node(front());
    while (node && node->next() && node->next() != toNode)
      node = node->next();

    if (node->next())
      return std::optional<E>(node->edge());
    else
      return std::nullopt;
  }

  std::optional<E> edgeTo(const L& toLabel) const
  {
    std::shared_ptr<EdgeNode<L, E>> node(front());
    while (node && node->next() && node->next()->label() != toLabel)
      node = node->next();

    if (node->next())
      return std::optional<E>(node->edge());
    else
      return std::nullopt;
  }

  friend std::ostream& operator<<(std::ostream& stream,
                                  const LinkedEdgeList<L, E>& list)
  {
    std::shared_ptr<EdgeNode<L, E>> tmp(list.front());
    stream << "[";
    while (tmp) {
      stream << *tmp;
      if (tmp->next()) {
        stream << ", ";
      }
      tmp = tmp->next();
    }
    stream << "]";
    return stream;
  }
};
} // namespace linked_lists