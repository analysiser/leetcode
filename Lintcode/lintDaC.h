//
//  lintDaC.h
//  Leetcode
//
//  Created by Xiao Li on 2/9/15.
//  Copyright (c) 2015 Xiao. All rights reserved.
//

#ifndef __Leetcode__lintDaC__
#define __Leetcode__lintDaC__

#include <stdio.h>
#include "core.h"

using namespace std;

namespace _lintcode {
    // file for solutions of Divide and Conquer
    namespace _LintDaC {
        
        // Validate BST
        bool isValidBST(TreeNode *root);
        
        // return max depth of binary tree
        int maxDepth(TreeNode *root);
        
        // judge if a binary tree is balanced
        bool isBalanced(TreeNode *root);
        
        // Binary Tree Maximum Path Sum
        int maxPathSum(TreeNode *root);
        
        // LCA in DaC
        TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *A, TreeNode *B);
        
    }
}

#endif /* defined(__Leetcode__lintDaC__) */
