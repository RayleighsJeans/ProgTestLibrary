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
  Node<L>* m_next;

 public:
  Node(L label, Node<L>* next) : m_label(label), m_next(next){};
  Node(L label) : Node(label, nullptr){};
  Node() : Node(L(), nullptr){};
  ~Node()
  {
    if (m_next)
      delete m_next;
    m_next = nullptr;
  };

  LabelType operator()() const { return m_label; }
  void operator()(LabelType label) { m_label = label; }
  Node<L>* next() const { return m_next; };

  void next(Node<L>* next)
  {
    if (next && next != m_next)
      delete m_next;
    m_next = next;
  }

  friend std::ostream& operator<<(std::ostream& stream, Node<L>& node)
  {
    stream << "{" << node() << ", ";
    if (node.next())
      stream << (*node.next())();
    else
      stream << "NULL";
    stream << "}";
    return stream;
  }
};


template <typename LabelType, typename EdgeType>
class EdgeNode : public Node<LabelType>
{
  using L = LabelType;
  using E = EdgeType;

 private:
  E m_edge;

 public:
  EdgeNode(L label, EdgeNode<L, E>* next, E edge)
      : Node<L>::Node(label, next), m_edge(edge){};
  EdgeNode(L label, EdgeNode<L, E>* next) : EdgeNode(label, next, E()){};
  EdgeNode(L label) : EdgeNode(label, nullptr, E()){};
  EdgeNode() : EdgeNode(L(), nullptr, E()){};

  EdgeNode(Node<L> node) : EdgeNode(node()){};
  EdgeNode(Node<L>* node) : EdgeNode((*node)()){};

  ~EdgeNode() = default;

  void next(EdgeNode<L, E>* next, E edge)
  {
    Node<L>::next(next);
    m_edge = edge;
  }

  EdgeNode<L, E>* next() const
  {
    return static_cast<EdgeNode<L, E>*>(Node<L>::next());
  }

  void edge(E edge) { m_edge = edge; }

  EdgeType edge() { return m_edge; }

  friend std::ostream& operator<<(std::ostream& stream, EdgeNode<L, E>& node)
  {
    stream << "{" << node() << "->(" << node.edge() << ")->";
    if (node.next())
      stream << (*node.next())();
    else
      stream << "NULL";
    stream << "}";
    return stream;
  }
};


template <typename LabelType>
class LinkedList
{
 private:
  using L = LabelType;

 private:
  size_t m_size = 0;
  Node<L>* m_head;
  Node<L>* m_tail;

 public:
  LinkedList(Node<L>* head) : m_head(head), m_tail(head)
  {
    if (head) {
      m_size++;

      Node<L>* tmp = head;
      while (tmp->next()) {
        tmp = tmp->next();
        m_size++;
      }
      m_tail = tmp;
    }
  };

  LinkedList() : LinkedList(nullptr){};

  ~LinkedList()
  {
    Node<L>* tmp = m_head;
    while (tmp->next()) {
      Node<L>* next = tmp->next();

      tmp->next(nullptr);
      delete tmp;

      tmp = next;
    }
    delete tmp;
  };

  void push_front(Node<L>* node)
  {
    node->next(m_head);
    m_head = node;
    m_size++;
  }

  void push_front(L value) { push_front(new Node<L>(value)); }

  void push_back(Node<L>* node)
  {
    node->next(nullptr);

    if (!m_head) {
      push_front(node);
      m_tail = node;
      return;
    }

    Node<L>* tmp = m_head;
    while (tmp->next()) {
      tmp = tmp->next();
    }
    tmp->next(node);
    m_tail = node;
    m_size++;
  }

  void push_back(L value) { push_back(new Node<L>(value)); }

  void insert(Node<L>* node, size_t position)
  {
    if (position > m_size) {
      std::cout << "Position out of range." << std::endl;
      delete node;
      return;
    }
    if (!position) {
      push_front(node);
      return;
    }
    if (position == m_size - 1) {
      push_back(node);
      return;
    }

    Node<L>* tmp = m_head;
    for (size_t i = 0; i < position - 1 && tmp; ++i) {
      tmp = tmp->next();
    }

    node->next(tmp->next());
    tmp->next(nullptr);
    tmp->next(node);
    m_size++;
  }

  void insert(L value, size_t position)
  {
    insert(new Node<L>(value), position);
  }

  void pop_front()
  {
    if (!m_head) {
      std::cout << "List is empty." << std::endl;
      return;
    }

    Node<L>* tmp = m_head;
    if (m_tail == m_head) {
      m_head = nullptr;
      m_tail = nullptr;
    }
    else {
      m_head = m_head->next();
    }
    tmp->next(nullptr);
    delete tmp;
    m_size--;
  }

  void pop_back()
  {
    if (!m_head) {
      std::cout << "List is empty." << std::endl;
      return;
    }

    if (m_tail == m_head) {
      m_head->next(nullptr);
      delete m_head;

      m_head = nullptr;
      m_tail = nullptr;
    }
    else {
      Node<L>* tmp = m_head;
      while (tmp->next()->next()) {
        tmp = tmp->next();
      }

      delete m_tail;
      m_tail = tmp;
      m_tail->next(nullptr);
    }
    m_size--;
  }

  void erase(size_t position)
  {
    if (position >= m_size) {
      std::cout << "Position out of range." << std::endl;
      return;
    }
    if (!position) {
      pop_front();
      return;
    }
    if (position == m_size - 1) {
      pop_back();
      return;
    }

    Node<L>* previousNode = m_head;
    for (size_t i = 0; i < position - 1 && previousNode; ++i) {
      previousNode = previousNode->next();
    }

    Node<L>* nodeToDelete = previousNode->next();
    Node<L>* followerNode = nodeToDelete->next();

    previousNode->next(nullptr);
    previousNode->next(followerNode);
    nodeToDelete->next(nullptr);

    delete nodeToDelete;

    m_size--;
  }

  Node<L>* front() const { return m_head; }

  Node<L>* back() const { return m_tail; }

  size_t size() const { return m_size; }

  friend std::ostream& operator<<(std::ostream& stream,
                                  const LinkedList<L>& list)
  {
    Node<L>* tmp = list.front();
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


template <typename LabelType, typename EdgeType>
class LinkedEdgeList : public LinkedList<LabelType>
{
 private:
  using L = LabelType;
  using E = EdgeType;

 public:
  LinkedEdgeList(EdgeNode<L, E>* head) : LinkedList<L>::LinkedList(head){};
  LinkedEdgeList() : LinkedList<L>::LinkedList(){};

  void push_front(L value, E edge)
  {
    EdgeNode<L, E>* node = new EdgeNode<L, E>(value, nullptr, edge);
    push_front(node);
  }

  void push_front(EdgeNode<L, E>* node)
  {
    node->next(static_cast<EdgeNode<L, E>*>(LinkedList<L>::front()),
               node->edge());
    LinkedList<L>::push_front(node);
  }

  void push_back(E edge, L value)
  {
    EdgeNode<L, E>* node = new EdgeNode<L, E>(value);
    push_back(edge, node);
  }

  void push_back(E edge, EdgeNode<L, E>* node)
  {
    node->next(nullptr, E());
    node->edge(E());
    static_cast<EdgeNode<L, E>*>(LinkedList<L>::back())->edge(edge);
    LinkedList<L>::push_back(node);
  }

  void insert(L value, E edge, size_t position)
  {
    insert(new EdgeNode<L, E>(value, nullptr, edge), position);
  }

  void insert(EdgeNode<L, E>* node, size_t position)
  {
    LinkedList<L>::insert(node, position);
  }

  void pop_back()
  {
    EdgeNode<L, E>* tmp = front();
    while (tmp->next()->next()) {
      tmp = static_cast<EdgeNode<L, E>*>(tmp->next());
    }
    E edge = tmp->edge();
    LinkedList<L>::pop_back();
    back()->edge(edge);
  }

  EdgeNode<L, E>* front() const
  {
    return static_cast<EdgeNode<L, E>*>(LinkedList<L>::front());
  }

  EdgeNode<L, E>* back() const
  {
    return static_cast<EdgeNode<L, E>*>(LinkedList<L>::back());
  }

  friend std::ostream& operator<<(std::ostream& stream,
                                  const LinkedEdgeList<L, E>& list)
  {
    EdgeNode<L, E>* tmp = list.front();
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