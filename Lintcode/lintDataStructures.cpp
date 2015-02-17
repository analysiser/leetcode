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
        
        namespace _BSTTraversal {
            
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
            
            // BST inorder stack traversal
            vector<int> stackInorderTraversal(TreeNode *root) {
                TreeNode *current = root;
                vector<int> res;
                stack<TreeNode *> st;
                
                while (!st.empty() || current) {
                    if (current) {
                        st.push(current);
                        current = current->left;
                    }
                    else {
                        current = st.top();
                        st.pop();
                        res.push_back(current->val);
                        if (current->right) {
                            current = current->right;
                        }
                    }
                }
                
                return res;
            }
            
            // inorder morris
            vector<int> morrisInorderTraversal(TreeNode *root) {
                vector<int> res;
                
                while (root) {
                    if (root->left) {
                        auto tmp = root->left;
                        while(tmp->right && tmp->right != root) {
                            tmp = tmp->right;
                        }
                        if (!tmp->right) {
                            tmp->right = root;
                            root = root->left;
                        }
                        else {
                            res.push_back(root->val);
                            tmp->right = nullptr;
                            root = root->right;
                        }
                    }
                    else {
                        res.push_back(root->val);
                        root = root->right;
                    }
                }
                
                return res;
            }
            
            
            // post order stack
            vector<int> stackPostorderTraversal(TreeNode *root) {
                // write your code here
                vector<int> res;
                stack<TreeNode *> st;
                
                if (root) {
                    st.push(root);
                    
                    while(!st.empty()) {
                        TreeNode *node = st.top();
                        st.pop();
                        res.push_back(node->val);
                        
                        if (node->left) {
                            st.push(node->left);
                        }
                        if (node->right) {
                            st.push(node->right);
                        }
                    }
                    
                    reverse(res.begin(), res.end());
                }
                
                return res;
            }
            
        } // end _BSTTraversal
        
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
        
        TreeNode* insertNode(TreeNode* root, TreeNode* node) {
            // write your code here
            if (!root) {
                return node;
            }
            if (!node) {
                return root;
            }
            TreeNode *newRoot = root;
            while(root) {
                if (node->val < root->val) {
                    auto tmp = root->left;
                    if (!tmp) {
                        root->left = node;
                        break;
                    }
                    else {
                        root = tmp;
                    }
                }
                else {
                    auto tmp = root->right;
                    if (!tmp) {
                        root->right = node;
                        break;
                    }
                    else {
                        root = tmp;
                    }
                }
            }
            return newRoot;
        } // end insertNode
        
        namespace _BSTIterator {
            
            // O(h) solution using stack
            BSTIteratorOh::BSTIteratorOh(TreeNode *root) {
                while(root) {
                    st.push(root);
                    root = root->left;
                }
            }
            
            bool BSTIteratorOh::hasNext() {
                return !st.empty();
            }
            
            TreeNode* BSTIteratorOh::next() {
                TreeNode *cur = st.top();
                st.pop();
                TreeNode *node = cur->right;
                while(node) {
                    st.push(node);
                    node = node->left;
                }
                return cur;
            }
            
            // O(1) solution with Morris Traversal
            BSTIteratorO1::BSTIteratorO1(TreeNode *root) {
                // write your code here
                while (root && root->left) {
                    TreeNode *tmp = root->left;
                    while (tmp->right && tmp->right != root) {
                        tmp = tmp->right;
                    }
                    if (!tmp->right) {
                        tmp->right = root;
                        root = root->left;
                    }
                    else {
                        break;
                    }
                }
                
                cur = root;
            }
            
            bool BSTIteratorO1::hasNext() {
                return (cur != nullptr);
            }
            
            TreeNode* BSTIteratorO1::next() {
                TreeNode *ret = cur;
                
                cur = cur->right;
                
                while (cur && cur->left) {
                    TreeNode *tmp = cur->left;
                    while(tmp->right && tmp->right != cur) {
                        tmp = tmp->right;
                    }
                    
                    if (!tmp->right) {
                        tmp->right = cur;
                        cur = cur->left;
                    }
                    else {
                        tmp->right = nullptr;
                        break;
                    }
                    
                }
                
                return ret;
            }
            
        } // end namespce _BSTIterator
        
        
        namespace _BSTDeleteNode {
            
            TreeNode *findMin(TreeNode *p) {
                if (p->left) {
                    return findMin(p->left);
                }
                return p;
            }
            
            TreeNode *removeMin(TreeNode *p) {
                if (p->left) {
                    p->left = removeMin(p->left);
                    return p;
                }
                return p->right;
            }
            
            TreeNode* removeNode(TreeNode* root, int value) {
                // write your code here
                if (!root) {
                    return nullptr;
                }
                if (value < root->val) {
                    root->left = removeNode(root->left, value);
                }
                else if (value > root->val) {
                    root->right = removeNode(root->right, value);
                }
                else {
                    TreeNode *l = root->left;
                    TreeNode *r = root->right;
                    
                    delete root;
                    
                    if (!l) {
                        return r;
                    }
                    if (!r) {
                        return l;
                    }
                    
                    TreeNode *minNode = findMin(r);
                    minNode->right = removeMin(r);
                    minNode->left = l;
                    
                    return minNode;
                }
                
                return root;
            }
            
        } // end namespace _BSTDeleteNode

        
        
        
    } // end _LintDataStructures
}