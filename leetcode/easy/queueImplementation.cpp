#include "../../include/header.hpp"


using namespace helper;


// Only use std::stack (two, ideally one).
// Only use: push to top, peek/pop from top, size, and is empty.
template <typename T>
class MyQueue
{
 public:
  MyQueue() = default;
  ~MyQueue() = default;

 private:
  std::stack<T> queue;

 public:
  void push(T x)
  {
    if (queue.empty()) {
      queue.push(x);
      return;
    }

    int oldTop = queue.top();
    queue.pop();
    this->push(x);
    queue.push(oldTop);
  }

  int pop()
  {
    int top = queue.top();
    queue.pop();
    return top;
  }

  int peek() { return queue.top(); }

  bool empty() { return queue.empty(); }

  void print(int i = 0)
  {
    if (this->empty())
      return;

    T element = queue.top();
    std::cout << ">> i:" << i << " - " << element << std::endl;

    queue.pop();
    print(i + 1);
    queue.push(element);

    return;
  }
}; // MyQueue


using NewQueue = MyQueue<int>;


int main()
{
  MyQueue<int>* myQueue = new MyQueue<int>();
  myQueue->push(1); // queue is: [1]
  myQueue->print();
  myQueue->push(2); // queue is: [1, 2] (leftmost is front of the queue)
  myQueue->print();

  print<char[], int>("top", myQueue->peek());     // return 1
  print<char[], int>("pop", myQueue->pop());      // return 1, queue is [2]
  print<char[], bool>("empty", myQueue->empty()); // return false

  NewQueue* newQueue = new NewQueue();

  return 0;
} // main