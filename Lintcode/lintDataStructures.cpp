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
        
        namespace _BFS {
            
            vector<vector<int>> levelOrderTwoArray(TreeNode *root) {
                // write your code here
                vector<vector<int>> res;
                if (root) {
                    
                    vector<TreeNode *> next, cur;
                    next.push_back(root);
                    
                    while (!next.empty()) {
                        vector<int> level;
                        for (int i = 0; i < next.size(); i++) {
                            level.push_back(next[i]->val);
                            if (next[i]->left) {
                                cur.push_back(next[i]->left);
                            }
                            if (next[i]->right) {
                                cur.push_back(next[i]->right);
                            }
                        }
                        res.push_back(level);
                        next = cur;
                        cur.clear();
                    }
                    
                }
                return res;
            }
            
            vector<vector<int>> levelOrderOneArray(TreeNode *root) {
                vector<vector<int>> res;
                if (root) {
                    vector<TreeNode *> next = { root };
                    int i = 0;
                    while (i < next.size()) {
                        vector<int> level;
                        int size = next.size();
                        
                        for (; i < size; i++) {
                            
                            level.push_back(next[i]->val);
                            
                            if (next[i]->left) {
                                next.push_back(next[i]->left);
                            }
                            if (next[i]->right) {
                                next.push_back(next[i]->right);
                            }
                        }
                        
                        res.push_back(level);
                    }
                    
                }
                return res;
            }
            
            vector<vector<int>> zigzagLevelOrder(TreeNode *root) {
                // write your code here
                vector<vector<int>> res;
                if (root) {
                    vector<TreeNode *> next = {root};
                    int i = 0;
                    while (i < next.size()) {
                        vector<int> level;
                        int size = next.size();
                        for (; i < size; i++) {
                            TreeNode *node = next[i];
                            level.push_back(node->val);
                            if (node->left) {
                                next.push_back(node->left);
                            }
                            if (node->right) {
                                next.push_back(node->right);
                            }
                        }
                        res.push_back(level);
                    }
                    
                    for (int i = 1; i < res.size(); i += 2) {
                        auto &level = res[i];
                        reverse(level.begin(), level.end());
                    }
                }
                return res;
            }
            
        } // end _BFS
        
        
    } // end _LintDataStructures
}