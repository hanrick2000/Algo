/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */

class Solution {
private:
    int getMinDepth(TreeNode* root) {
        if(root == nullptr) return INT_MAX;

        int leftMin = getMinDepth(root->left);
        int rightMin = getMinDepth(root->right);

        int min = std::min(leftMin, rightMin);
        if(min == INT_MAX) return 1;
        else return min + 1;
    }
public:
    /**
     * @param root: The root of binary tree
     * @return: An integer
     */
    int minDepth(TreeNode * root) {
        int depth = getMinDepth(root);
        if(depth == INT_MAX) return 0;
        else return depth;
    }
};

// Iterative DFS
class Solution {
public:
    /**
     * @param root: The root of binary tree
     * @return: An integer
     */
    int minDepth(TreeNode * root) {
        if(root == nullptr) return 0;

        auto node = root;
        int minDepth = INT_MAX;
        int depth = 1;
        std::stack<TreeNode*> s;
        std::stack<int> depthS;
        s.push(node);
        depthS.push(depth);

        while(!s.empty()) {
            node = s.top();
            s.pop();
            depth = depthS.top();
            depthS.pop();

            if(node->left == nullptr && node->right == nullptr) {
                minDepth = std::min(minDepth, depth);
            }

            if(node->left != nullptr) {
                s.push(node->left);
                depthS.push(depth + 1);
            }

            if(node->right != nullptr) {
                s.push(node->right);
                depthS.push(depth + 1);
            }
        }
        return minDepth;
    }
};