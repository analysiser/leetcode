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
        
        
    }
}