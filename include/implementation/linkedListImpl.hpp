#pragma once


#include "../header.hpp"


using namespace helper;

namespace linked_lists
{
template <typename LabelType>
class Node
{
  using L = LabelType;

 private:
  L m_label;
  Node<L>* m_next = nullptr;

 public:
  Node() {};
  Node(L label) : m_label(label) {};
  Node(L label, Node<L>* next) : Node(label), m_next(next) {};

  void operator()(LabelType label) { m_label = label; }
  void next(Node<L>* next) { m_next = next; }
  LabelType operator()() const { return m_label; }
  Node<L>* next() const { return m_next; };
};


template <typename LabelType, typename EdgeType>
class EdgeNode : public Node<LabelType>
{
  using L = LabelType;
  using E = EdgeType;

 private:
  E m_edge;

 public:
  EdgeNode() : Node<L>::Node() {};
  EdgeNode(L label) : Node<L>::Node(label) {};
  EdgeNode(L label, EdgeNode<L, E>* next) : Node<L>::Node(label, next) {};
  EdgeNode(L label, EdgeNode<L, E>* next, E edge)
      : EdgeNode(label, next), m_edge(edge) {};

  //   void operator()(LabelType label) { m_label = label; }
  //   void next(Node<L, E>* next, E edge = 0)
  //   {
  //     m_next = next;
  //     m_edge = edge;
  //   }
  //
  //   LabelType operator()() const { return m_label; }
  //   Node<L, E>* next() const { return m_next };
  //   EdgeType edge() const { return m_edge; }
};
//
//
// template <typename LabelType, typename EdgeType>
// class LinkedList
// {
//   using L = LabelType;
//   using E = EdgeType;
//
//  private:
//   Node<L, E>* m_head;
//
//  public:
//   LinkedList() : m_head(nullptr) {}
//
//   void push_front(L value, E edge = 0)
//   {
//     Node<L, E>* newNode = new Node<L, E>(value, edge);
//     newNode->next(m_head);
//     m_head = newNode;
//   }
//
//   void push_back(L value, E edge = 0)
//   {
//     Node<L, E>* newNode = new Node<T>();
//     newNode->m_value = value;
//     newNode->next = nullptr;
//
//     if (!m_head) {
//       m_head = newNode;
//       return;
//     }
//
//     Node<T>* temp = m_head;
//     while (temp->next) {
//       temp = temp->next;
//     }
//     temp->next = newNode;
//   }
//
//   void insert(T value, size_t position)
//   {
//     if (!position) {
//       push_front(value);
//       return;
//     }
//
//     Node<T>* newNode = new Node<T>();
//     newNode->m_value = value;
//
//     Node<T>* temp = m_head;
//     for (int i = 0; i < position - 1 && temp; ++i) {
//       temp = temp->next;
//     }
//
//     if (!temp) {
//       std::cout << "Position out of range." << std::endl;
//       delete newNode;
//       return;
//     }
//
//     newNode->next = temp->next;
//     temp->next = newNode;
//   }
//
//   void pop_front()
//   {
//     if (!m_head) {
//       std::cout << "List is empty." << std::endl;
//       return;
//     }
//
//     Node<T>* temp = m_head;
//     m_head = m_head->next;
//     delete temp;
//   }
//
//   void pop_back()
//   {
//     if (!m_head) {
//       std::cout << "List is empty." << std::endl;
//       return;
//     }
//
//     if (!m_head->next) {
//       delete m_head;
//       m_head = nullptr;
//       return;
//     }
//
//     Node<T>* temp = m_head;
//     while (temp->next->next) {
//       temp = temp->next;
//     }
//     delete temp->next;
//     temp->next = nullptr;
//   }
//
//   void erase(size_t position)
//   {
//     if (!position) {
//       pop_front();
//       return;
//     }
//
//     Node<T>* temp = m_head;
//     for (int i = 0; i < position - 1 && temp; ++i) {
//       temp = temp->next;
//     }
//
//     if (!temp || !temp->next) {
//       std::cout << "Position out of range." << std::endl;
//       return;
//     }
//
//     Node<T>* nodeToDelete = temp->next;
//     temp->next = temp->next->next;
//     delete nodeToDelete;
//   }
//
//   Node<T>* front() const { return m_head; }
//
//   Node<T>* back() const
//   {
//     Node<T>* temp = m_head;
//     while (temp) {
//       if (!temp->next)
//         break;
//       temp = temp->next;
//     }
//     return temp;
//   }
//
//   friend std::ostream& operator<<(std::ostream& stream, const LinkedList&
//   list)
//   {
//     Node<T>* temp = list.front();
//     stream << "[";
//     while (temp) {
//       stream << temp->m_value;
//       if (temp->next) {
//         stream << ", ";
//       }
//       temp = temp->next;
//     }
//     stream << "]";
//     return stream;
//   }
// };
} // namespace linked_lists