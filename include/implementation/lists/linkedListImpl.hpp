#pragma once

#include <memory>
#include <optional>

#include "nodesImpl.hpp"


namespace linked_lists
{
template <typename LabelType>
class LinkedList
{
 private:
  using L = LabelType;

 private:
  size_t m_size = 0;
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

 public:
  LinkedList(Node<L>* node) : m_head(node), m_tail(m_head)
  {
    if (node)
      m_size++;

    if (node->next()) {
      std::shared_ptr<Node<L>> tmp(node);
      while (tmp->next()) {
        tmp = tmp->next();
        m_size++;
      }
      m_tail = tmp;
    }
  };

  LinkedList(const L label) : LinkedList(new Node<L>(label)) {};

  LinkedList() : LinkedList(nullptr) {};

  ~LinkedList() {
    // Node<L>* tmp = m_head;
    // while (tmp && tmp->next()) {
    //   Node<L>* next = tmp->next().get();

    //   tmp->next(nullptr);
    //   delete tmp;

    //   tmp = next;
    // }
    // delete tmp;

    // if (m_head != m_tail)
    //   m_tail.reset();
    // m_head.reset();
  };

  void push_front(Node<L>* node)
  {
    node->next(m_head);
    head(std::shared_ptr<Node<L>>(node));
    m_size++;
  }

  void push_front(const L value) { push_front(new Node<L>(value)); }

  // void push_back(Node<L>* node)
  // {
  //   node->next(nullptr);

  //   if (!m_head) {
  //     push_front(node);
  //     tail(std::shared_ptr<Node<L>>(node));
  //     return;
  //   }

  //   std::shared_ptr<Node<L>> tmp = m_head;
  //   while (tmp->next()) {
  //     tmp = tmp->next();
  //   }
  //   tmp->next(node);
  //   tail(std::shared_ptr<Node<L>>(node));
  //   m_size++;
  // }

  // void push_back(const L value) { push_back(new Node<L>(value)); }

  // void insert(Node<L>* node, const size_t position)
  // {
  //   if (position > m_size) {
  //     std::cout << "Position out of range." << std::endl;
  //     delete node;
  //     return;
  //   }
  //   if (!position) {
  //     push_front(node);
  //     return;
  //   }
  //   if (position == m_size - 1) {
  //     push_back(node);
  //     return;
  //   }

  //   Node<L>* tmp = m_head;
  //   for (size_t i = 0; i < position - 1 && tmp; ++i) {
  //     tmp = tmp->next();
  //   }

  //   node->next(tmp->next());
  //   tmp->next(nullptr);
  //   tmp->next(node);
  //   m_size++;
  // }

  // void insert(const L value, const size_t position)
  // {
  //   insert(new Node<L>(value), position);
  // }

  // void pop_front()
  // {
  //   if (!m_head) {
  //     std::cout << "List is empty." << std::endl;
  //     return;
  //   }

  //   std::shared_ptr<Node<L>> tmp = m_head;
  //   if (m_tail == m_head) {
  //     m_head = nullptr;
  //     m_tail = nullptr;
  //   }
  //   else {
  //     head(m_head->next());
  //   }
  //   tmp->next(nullptr);
  //   if (tmp && tmp.unique())
  //     tmp.reset();
  //   m_size--;
  // }

  // void pop_back()
  // {
  //   if (!m_head) {
  //     std::cout << "List is empty." << std::endl;
  //     return;
  //   }

  //   if (m_tail == m_head) {
  //     m_head->next(nullptr);
  //     if (m_head && m_head.unique())
  //       m_head.reset();

  //     m_head = nullptr;
  //     m_tail = nullptr;
  //   }
  //   else {
  //     std::shared_ptr<Node<L>> tmp = m_head;
  //     while (tmp->next()->next()) {
  //       tmp = tmp->next();
  //     }

  //     if (m_tail && m_tail.unique())
  //       m_tail.reset();
  //     m_tail = tmp;
  //     m_tail->next(nullptr);
  //   }
  //   m_size--;
  // }

  // void erase(const size_t position, const bool debug = true)
  // {
  //   if (position >= m_size) {
  //     if (debug)
  //       std::cout << "Position out of range." << std::endl;
  //     return;
  //   }
  //   if (!position) {
  //     pop_front();
  //     return;
  //   }
  //   if (position == m_size - 1) {
  //     pop_back();
  //     return;
  //   }

  //   std::shared_ptr<Node<L>> previousNode = m_head;
  //   for (size_t i = 0; i < position - 1 && previousNode; ++i) {
  //     previousNode = previousNode->next();
  //   }

  //   std::shared_ptr<Node<L>> nodeToDelete = previousNode->next();
  //   std::shared_ptr<Node<L>> followerNode = nodeToDelete->next();

  //   previousNode->next(nullptr);
  //   previousNode->next(followerNode);
  //   nodeToDelete->next(nullptr);

  //   if (nodeToDelete && nodeToDelete.unique())
  //     nodeToDelete.reset();

  //   m_size--;
  // }

  // void erase(Node<L>* node) { erase(find(node), false); }

  // void erase(const L label) { erase(find(label), false); }

  // size_t find(Node<L>* node, const bool debug = true) const
  // {
  //   size_t position = 0;
  //   std::shared_ptr<Node<L>> tmp = m_head;
  //   while (node != tmp && tmp) {
  //     position++;
  //     tmp = tmp->next();
  //   }

  //   if (debug && (position == m_size))
  //     std::cout << "Node not in list." << std::endl;
  //   return position;
  // }

  // size_t find(const L& label, const bool debug = true) const
  // {
  //   size_t position = 0;
  //   std::shared_ptr<Node<L>> node = m_head;
  //   while (node && label != node->label()) {
  //     position++;
  //     node = node->next();
  //   }

  //   if (debug && (position == m_size))
  //     std::cout << "Key not in list." << std::endl;
  //   return position;
  // }

  const std::shared_ptr<Node<L>>& front() const { return m_head; }

  const std::shared_ptr<Node<L>>& back() const { return m_tail; }

  // const std::shared_ptr<Node<L>>& at(const size_t position) const
  // {
  //   if (position >= m_size)
  //     return nullptr;
  //   std::shared_ptr<Node<L>> node = m_head;
  //   for (size_t i = 0; i < position && node; ++i) {
  //     node = node->next();
  //   }
  //   return node;
  // }

  size_t size() const { return m_size; }

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


// template <typename LabelType, typename EdgeType>
// class LinkedEdgeList : public LinkedList<LabelType>
// {
//  private:
//   using L = LabelType;
//   using E = EdgeType;

//  public:
//   LinkedEdgeList(EdgeNode<L, E>* head) : LinkedList<L>::LinkedList(head){};

//   LinkedEdgeList(const L& label, const E& edge)
//       : LinkedEdgeList(new EdgeNode<L, E>(label, nullptr, edge)){};

//   LinkedEdgeList() : LinkedList<L>::LinkedList(){};

//   void push_front(const L& value, const E& edge)
//   {
//     EdgeNode<L, E>* node = new EdgeNode<L, E>(value, nullptr, edge);
//     push_front(node);
//   }

//   void push_front(EdgeNode<L, E>* node)
//   {
//     node->next(static_cast<EdgeNode<L, E>*>(LinkedList<L>::front()),
//                node->edge());
//     LinkedList<L>::push_front(node);
//   }

//   void push_back(const E& edge, const L& value)
//   {
//     EdgeNode<L, E>* node = new EdgeNode<L, E>(value);
//     push_back(edge, node);
//   }

//   void push_back(const E& edge, EdgeNode<L, E>* node)
//   {
//     node->next(nullptr, E());
//     node->edge(E());
//     static_cast<EdgeNode<L, E>*>(LinkedList<L>::back())->edge(edge);
//     LinkedList<L>::push_back(node);
//   }

//   void insert(const L& value, const E& edge, const size_t position)
//   {
//     insert(new EdgeNode<L, E>(value, nullptr, edge), position);
//   }

//   void insert(EdgeNode<L, E>* node, size_t position)
//   {
//     LinkedList<L>::insert(node, position);
//   }

//   void pop_back()
//   {
//     EdgeNode<L, E>* tmp = front();
//     while (tmp->next()->next()) {
//       tmp = static_cast<EdgeNode<L, E>*>(tmp->next());
//     }
//     E edge = tmp->edge();
//     LinkedList<L>::pop_back();
//     back()->edge(edge);
//   }

//   EdgeNode<L, E>* front() const
//   {
//     return static_cast<EdgeNode<L, E>*>(LinkedList<L>::front());
//   }

//   EdgeNode<L, E>* back() const
//   {
//     return static_cast<EdgeNode<L, E>*>(LinkedList<L>::back());
//   }

//   std::optional<E> edgeTo(EdgeNode<L, E>* toNode) const
//   {
//     EdgeNode<L, E>* node = front();
//     while (node && node->next() && node->next() != toNode)
//       node = node->next();

//     if (node->next())
//       return std::optional<E>(node->edge());
//     else
//       return std::nullopt;
//   }

//   std::optional<E> edgeTo(const L& toLabel) const
//   {
//     EdgeNode<L, E>* node = front();
//     while (node && node->next() && node->next()->label() != toLabel)
//       node = node->next();

//     if (node->next())
//       return std::optional<E>(node->edge());
//     else
//       return std::nullopt;
//   }

//   friend std::ostream& operator<<(std::ostream& stream,
//                                   const LinkedEdgeList<L, E>& list)
//   {
//     EdgeNode<L, E>* tmp = list.front();
//     stream << "[";
//     while (tmp) {
//       stream << *tmp;
//       if (tmp->next()) {
//         stream << ", ";
//       }
//       tmp = tmp->next();
//     }
//     stream << "]";
//     return stream;
//   }
// };
} // namespace linked_lists