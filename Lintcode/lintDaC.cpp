//
//  lintDaC.cpp
//  Leetcode
//
//  Created by Xiao Li on 2/9/15.
//  Copyright (c) 2015 Xiao. All rights reserved.
//

#include "lintDaC.h"

namespace _lintcode {
    // file for solutions of Divide and Conquer
    namespace _LintDaC {
        /**
         * @param root: The root of binary tree.
         * @return: True if the binary tree is BST, or false
         */
        
#define MIN_VALUE   LONG_LONG_MIN
#define MAX_VALUE   LONG_LONG_MAX
        
        bool isValidBSTHelpr(TreeNode *node, int64_t &max, int64_t &min) {
            if (!node) {
                max = MIN_VALUE;
                min = MAX_VALUE;
                return true;
            }
            int64_t lmax = MIN_VALUE;
            int64_t rmax = MIN_VALUE;
            int64_t lmin = MAX_VALUE;
            int64_t rmin = MAX_VALUE;
            bool left = isValidBSTHelpr(node->left, lmax, lmin);
            bool right = isValidBSTHelpr(node->right, rmax, rmin);
            if (!left || !right || !(int64_t(node->val) > lmax) || !(int64_t(node->val) < rmin)) {
                return false;
            }
            else {
                if (node->val < lmin) {
                    min = node->val;
                }
                if (node->val > rmax) {
                    max = node->val;
                }
                return true;
            }
        }
        
        bool isValidBST(TreeNode *root) {
            // write your code here
            int64_t max = MIN_VALUE;
            int64_t min = MAX_VALUE;
            return isValidBSTHelpr(root, max, min);
        }
        
        //
        int maxDepth(TreeNode *root) {
            // write your code here
            if (!root) {
                return 0;
            }
            return max(maxDepth(root->left), maxDepth(root->right)) + 1;
        }
        
        int treeHeight(TreeNode *root) {
            if (!root) {
                return 0;
            }
            return max(treeHeight(root->left), treeHeight(root->right)) + 1;
        }
        
        bool isBalanced(TreeNode *root) {
            // write your code here
            if (!root) {
                return true;
            }
            bool l = isBalanced(root->left);
            bool r = isBalanced(root->right);
            if (l && r) {
                int lh = treeHeight(root->left);
                int rh = treeHeight(root->right);
                if (abs(lh - rh) <= 1) {
                    return true;
                }
                else {
                    return false;
                }
            }
            else {
                return false;
            }
            
        }
        
        int maxPathHelper(TreeNode *node, int &res) {
            if (node) {
                int leftMax = maxPathHelper(node->left, res);
                int rightMax = maxPathHelper(node->right, res);
                
                if (leftMax == INT_MIN && rightMax == INT_MIN) {
                    if (node->val > res) {
                        res = node->val;
                    }
                    return node->val;
                }
                else if (leftMax == INT_MIN || rightMax == INT_MIN) {
                    int maxLen = max(leftMax, rightMax) + node->val;
                    maxLen = max(maxLen, node->val);
                    if (maxLen > res) {
                        res = maxLen;
                    }
                    return maxLen;
                }
                else {
                    int maxLen = max(leftMax, rightMax) + node->val;
                    maxLen = max(maxLen, node->val);
                    int maxOverLen = max(leftMax + rightMax + node->val, node->val);
                    
                    if (maxLen > res) {
                        res = maxLen;
                    }
                    if (maxOverLen > res) {
                        res = maxOverLen;
                    }
                    return maxLen;
                    
                }
                
            }
            return INT_MIN;
        }
        
        int maxPathSum(TreeNode *root) {
            // write your code here
            int maxsum = INT_MIN;
            maxPathHelper(root, maxsum);
            return maxsum;
        }
        
        // LCA
        TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *A, TreeNode *B) {
            if (!root || root == A || root == B) {
                return root;
            }
            
            TreeNode *left = lowestCommonAncestor(root->left, A, B);
            TreeNode *right = lowestCommonAncestor(root->right, A, B);
            
            if (left && right) {
                return root;
            }
            if (left) {
                return left;
            }
            if (right) {
                return right;
            }
            
            return nullptr;
        }
        
        vector<int> searchRange(TreeNode* root, int k1, int k2) {
            // write your code here
            vector<int> res;
            if (!root || k2 < k1) {
                return res;
            }
            vector<int> left, right;
            if (root->val > k1) {
                left = searchRange(root->left, k1, k2);
            }
            if (root->val < k2) {
                right = searchRange(root->right, k1, k2);
            }
            
            res.insert(res.end(), left.begin(), left.end());
            
            if (root->val >= k1 && root->val <= k2) {
                res.push_back(root->val);
            }
            res.insert(res.end(), right.begin(), right.end());
            
            return res;
        }
        
        int64_t doPower(int a, int b, int n) {
            if (n == 0) {
                return 1%b;
            }
            if (n == 1) {
                return a%b;
            }
            if (a == 1) {
                return 1;
            }
            
            int64_t ret = doPower(a, b, n/2);
            ret *= ret;
            ret %= b;
            
            if (n % 2) {
                ret *= doPower(a, b, 1);
                ret %= b;
            }
            
            return ret;
        }
        
        int fastPower(int a, int b, int n) {
            return static_cast<int>(doPower(a, b, n));
        }
        
        
    } // end namespace DaC
}