#pragma once

#include <iostream>
#include <memory>


namespace linked_lists
{
template <typename LabelType>
class EmptyNode
{
 private:
  using L = LabelType;

  L m_label;

 public:
  EmptyNode(L label) : m_label(label){};

  EmptyNode() : EmptyNode(L()){};

  ~EmptyNode() = default;

  L label() const { return m_label; }

  L operator()() const { return m_label; }

  void operator()(const L& label) { m_label = label; }

  void label(const L& label) { m_label = label; }

  friend std::ostream& operator<<(std::ostream& stream,
                                  const EmptyNode<L>& node)
  {
    return (stream << "{" << node() << "}");
  }
};


template <typename LabelType>
class Node : public EmptyNode<LabelType>
{
 private:
  using L = LabelType;

  std::shared_ptr<Node<L>> m_next = nullptr;

 public:
  Node(const L& label, std::shared_ptr<Node<L>> node)
      : EmptyNode<L>::EmptyNode(label), m_next(node){};

  Node(const L& label) : Node(label, nullptr){};

  Node() : Node(L(), nullptr){};

  ~Node() = default;

  std::shared_ptr<Node<L>> next() const { return m_next; };

  void next(std::shared_ptr<Node<L>> node)
  {
    if (node && node != m_next)
      if (m_next && (m_next.use_count() == 1))
        m_next.reset();
    m_next.swap(node);
  }

  friend std::ostream& operator<<(std::ostream& stream, const Node<L>& node)
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
 private:
  using L = LabelType;
  using E = EdgeType;

  E m_edge;

 public:
  EdgeNode(const L& label, std::shared_ptr<EdgeNode<L, E>> next, const E& edge)
      : Node<L>::Node(label, next), m_edge(edge){};

  EdgeNode(const L& label, std::shared_ptr<EdgeNode<L, E>> next)
      : EdgeNode(label, next, E()){};

  EdgeNode(const L& label) : EdgeNode(label, nullptr, E()){};

  EdgeNode() : EdgeNode(L(), nullptr, E()){};

  ~EdgeNode() = default;

  void edge(const E& newEdge) { m_edge = newEdge; }

  E edge() const { return m_edge; }

  void next(std::shared_ptr<EdgeNode<L, E>> node, const E& newEdge)
  {
    Node<L>::next(node);
    edge(newEdge);
  }

  std::shared_ptr<EdgeNode<L, E>> next() const
  {
    return std::static_pointer_cast<EdgeNode<L, E>>(Node<L>::next());
  }

  friend std::ostream& operator<<(std::ostream& stream,
                                  const EdgeNode<L, E>& node)
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
} // namespace linked_lists