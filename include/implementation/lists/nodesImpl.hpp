#pragma once


namespace linked_lists
{
template <typename LabelType>
class EmptyNode
{
  using L = LabelType;

 private:
  L m_label;

 public:
  EmptyNode(L label) : m_label(label){};

  EmptyNode() : EmptyNode(L()){};

  ~EmptyNode() = default;

  LabelType label() const { return m_label; }

  LabelType operator()() const { return m_label; }

  void operator()(const LabelType& label) { m_label = label; }

  void label(const LabelType& label) { m_label = label; }

  friend std::ostream& operator<<(std::ostream& stream,
                                  const EmptyNode<L>& node)
  {
    return (stream << "{" << node() << "}");
  }
};


template <typename LabelType>
class Node : public EmptyNode<LabelType>
{
  using L = LabelType;

 private:
  L m_label;
  Node<L>* m_next;

 public:
  Node(const L& label, Node<L>* next)
      : EmptyNode<LabelType>::EmptyNode(label), m_next(next){};

  Node(const L& label) : Node(label, nullptr){};

  Node() : Node(L(), nullptr){};

  ~Node()
  {
    if (m_next)
      delete m_next;
    m_next = nullptr;
  };

  Node<L>* next() const { return m_next; };

  void next(Node<L>* next)
  {
    if (next && next != m_next)
      delete m_next;
    m_next = next;
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
  using L = LabelType;
  using E = EdgeType;

 private:
  E m_edge;

 public:
  EdgeNode(const L& label, EdgeNode<L, E>* next, const E& edge)
      : Node<L>::Node(label, next), m_edge(edge){};

  EdgeNode(const L& label, EdgeNode<L, E>* next) : EdgeNode(label, next, E()){};

  EdgeNode(const L& label) : EdgeNode(label, nullptr, E()){};

  EdgeNode() : EdgeNode(L(), nullptr, E()){};

  EdgeNode(Node<L> node) : EdgeNode(node()){};

  EdgeNode(Node<L>* node) : EdgeNode((*node)()){};

  ~EdgeNode() = default;

  void next(EdgeNode<L, E>* next, const E edge)
  {
    Node<L>::next(next);
    m_edge = edge;
  }

  EdgeNode<L, E>* next() const
  {
    return static_cast<EdgeNode<L, E>*>(Node<L>::next());
  }

  void edge(const E& edge) { m_edge = edge; }

  EdgeType edge() const { return m_edge; }

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