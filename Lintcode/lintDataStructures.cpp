//
//  lintDataStructures.cpp
//  Leetcode
//
//  Created by Xiao Li on 2/12/15.
//  Copyright (c) 2015 Xiao. All rights reserved.
//

#include "lintDataStructures.h"

namespace _lintcode {
    
    namespace _LintDataStructures {
        
        namespace _BSTPreorderTraversal {
            
            void preorderTraversalHelper(TreeNode *node, vector<int> &res) {
                if (node) {
                    res.push_back(node->val);
                    preorderTraversalHelper(node->left, res);
                    preorderTraversalHelper(node->right, res);
                }
            }
            
            // recursive solution
            vector<int> recurPreorderTraversal(TreeNode *root) {
                vector<int> res;
                preorderTraversalHelper(root, res);
                return res;
            }
            
            // stack solution
            vector<int> stackPreorderTraversal(TreeNode *root) {
                vector<int> res;
                
                if (root) {
                    stack<TreeNode *> st;
                    st.push(root);
                    
                    while (!st.empty()) {
                        
                        auto node = st.top();
                        res.push_back(node->val);
                        st.pop();
                        
                        if (node->right) {
                            st.push(node->right);
                        }
                        if (node->left) {
                            st.push(node->left);
                        }
                        
                    } // end while
                }
                
                return res;
            }
            
            // Morris traversal
            vector<int> morrisPreorderTraversal(TreeNode *root) {
                vector<int> res;
                while (root) {
                    auto tmp = root->left;
                    if (tmp) {
                        while (tmp->right && tmp->right != root) {
                            tmp = tmp->right;
                        }
                        if (!tmp->right) {
                            res.push_back(root->val);
                            tmp->right = root;
                            root = root->left;
                        }
                        else {
                            root = root->right;
                            tmp->right = nullptr;
                        }
                        
                    }
                    else {
                        res.push_back(root->val);
                        root = root->right;
                    }
                }
                return res;
            }
            
            
        } // end _BSTPreorderTraversal
        
        
    } // end _LintDataStructures
}