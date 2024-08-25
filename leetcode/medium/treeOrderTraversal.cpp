#include "../../include/header.hpp"


/// Definition for a binary tree node.
struct TreeNode
{
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right)
  {}
};


std::vector<std::vector<int>> levelOrder(TreeNode* root)
{
  std::vector<std::vector<int>> order;
  std::list<std::list<TreeNode*>> queue;

  if (root) {
    queue.push_back({root});
    order.push_back({root->val});

    while (!queue.empty()) {
      std::list<TreeNode*> thisLevel = queue.front();
      queue.pop_front();

      std::list<TreeNode*> nextLevel;
      std::vector<int> thisOrder;

      while (!thisLevel.empty()) {
        TreeNode* thisNode = thisLevel.front();
        thisLevel.pop_front();

        std::vector<int> thisLevel;
        if (thisNode->left) {
          nextLevel.push_back(thisNode->left);
          thisOrder.push_back(thisNode->left->val);
        }
        if (thisNode->right) {
          nextLevel.push_back(thisNode->right);
          thisOrder.push_back(thisNode->right->val);
        }

        for (auto x : nextLevel)
          std::cout << x->val << ", ";
        std::cout << std::endl;
      }
      if (!nextLevel.empty())
        queue.push_back(nextLevel);
      if (!thisOrder.empty())
        order.push_back(thisOrder);
    }
  }
  return order;
}


int main()
{
  auto root = new TreeNode(3, new TreeNode(9),
                           new TreeNode(20, new TreeNode(15), new TreeNode(7)));
  auto result = levelOrder(root);
  helper::print<char[], int>("result", result);

  return 0;
}