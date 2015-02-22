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

        
        namespace _LinkedList {
            
            // remove duplicates
            ListNode *deleteDuplicates(ListNode *head) {
                // write your code here
                if (!head || !head->next) {
                    return head;
                }
                ListNode *cur = head;
                
                while (cur->next) {
                    if (cur->val == cur->next->val) {
                        auto tmp = cur->next;
                        cur->next = tmp->next;
                        delete tmp;
                    }
                    else {
                        cur = cur->next;
                    }
                }
                
                return head;
            }
            
            // Remove Duplicates from Sorted List II
            ListNode *deleteDuplicates2(ListNode *head) {
                if (!head || !head->next) {
                    return head;
                }
                
                ListNode *dummy = new ListNode(0);
                dummy->next = head;
                ListNode *cur = dummy;
                while (cur->next) {
                    auto start = cur->next;
                    auto end = start;
                    while (end->next && end->next->val == start->val) {
                        end = end->next;
                    }
                    
                    if (start != end) {
                        cur->next = end->next;
                        end->next = nullptr;
                        while (start != nullptr) {
                            auto tmp = start;
                            start = start->next;
                            delete tmp;
                        }
                    }
                    else {
                        cur = start;
                    }
                }
                
                auto newHead = dummy->next;
                delete dummy;
                
                return newHead;
            }
            
            // Reverse
            ListNode *reverse(ListNode *head) {
                // write your code here
                if (!head || !head->next) {
                    return head;
                }
                
                ListNode *newHead = head;
                ListNode *a = head;
                ListNode *b = a->next;
                
                while (b) {
                    a->next = b->next;
                    b->next = newHead;
                    newHead = b;
                    b = a->next;
                }
                
                return newHead;
            } // end reverse
            
            ListNode *reverseBetween(ListNode *head, int m, int n) {
                // write your code here
                if (!head || !head->next || n <= m) {
                    return head;
                }
                
                decltype(head) ls, rs, be, en, a, b, newHead;
                ListNode *dummy = new ListNode(0);
                dummy->next = head;
                
                ListNode *tmp = dummy;
                int count = 0;
                while (tmp) {
                    if (count + 1 == m) {
                        ls = tmp;
                        be = tmp->next;
                    }
                    
                    if (count == n) {
                        en = tmp;
                        rs = tmp->next;
                        
                        // begin reverse
                        en->next = nullptr;
                        a = be;
                        b = a->next;
                        newHead = a;
                        while (b) {
                            a->next = b->next;
                            b->next = newHead;
                            newHead = b;
                            b = a->next;
                        }
                        a->next = rs;
                        ls->next = newHead;
                        
                        break;
                        // end reverse
                    }
                    count++;
                    tmp = tmp->next;
                }
                
                newHead = dummy->next;
                delete dummy;
                return newHead;
            } // end Reverse II
            
            
            ListNode *partition(ListNode *head, int x) {
                if (!head || !head->next) {
                    return head;
                }
                
                // write your code here
                ListNode *dummy1 = new ListNode(0);
                dummy1->next = head;
                ListNode *dummy2 = new ListNode(0);
                
                ListNode *cur1 = head;
                ListNode *cur2 = dummy2;
                ListNode *prev = dummy1;
                
                while (cur1) {
                    if (cur1->val >= x) {
                        prev->next = cur1->next;
                        cur1->next = nullptr;
                        
                        cur2->next = cur1;
                        cur2 = cur2->next;
                        
                        cur1 = prev->next;
                        
                    }
                    else {
                        prev = cur1;
                        cur1 = cur1->next;
                    }
                }
                
                prev->next = dummy2->next;
                ListNode *newHead = dummy1->next;
                delete dummy1;
                delete dummy2;
                
                return newHead;
            } // end Partition
            
            
            ListNode *mergeList(ListNode *l1, ListNode *l2) {
                if (!l1) {
                    return l2;
                }
                if (!l2) {
                    return l1;
                }
                
                ListNode *dummy = new ListNode(0);
                ListNode *cur = dummy;
                while (l1 && l2) {
                    if (l1->val <= l2->val) {
                        cur->next = l1;
                        l1 = l1->next;
                    }
                    else {
                        cur->next = l2;
                        l2 = l2->next;
                    }
                    cur = cur->next;
                    cur->next = nullptr;
                }
                
                if (l1) {
                    cur->next = l1;
                }
                if (l2) {
                    cur->next = l2;
                }
                
                auto head = dummy->next;
                delete dummy;
                return head;
            }
            
            ListNode *splitList(ListNode *head) {
                if (!head || !head->next) {
                    return nullptr;
                }
                
                auto cur = head;
                auto cur2 = head;
                while (cur2 && cur2->next && cur2->next->next) {
                    cur = cur->next;
                    cur2 = cur2->next->next;
                }
                
                cur2 = cur->next;
                cur->next = nullptr;
                return cur2;
            }
            
            
            ListNode *sortList(ListNode *head) {
                // write your code here
                if (!head || !head->next) {
                    return head;
                }
                
                ListNode *another = splitList(head);
                auto l1 = sortList(head);
                auto l2 = sortList(another);
                return mergeList(l1, l2);
                
            } // end sortList
            
            
            // Reordered List
            void reorderList(ListNode *head) {
                
                if (!head || !head->next || !head->next->next) {
                    return;
                }
                
                vector<ListNode *> vec;
                auto p = head;
                while (p) {
                    vec.push_back(p);
                    p = p->next;
                }
                
                int t = vec.size()/2;
                vec[vec.size()-t-1]->next = nullptr;
                auto cur = head;
                for (int i = 0; i < t; i++) {
                    int idx = vec.size()-1-i;
                    vec[idx]->next = cur->next;
                    cur->next = vec[idx];
                    cur = cur->next->next;
                }
                
//                if (!head || !head->next || !head->next->next) {
//                    return;
//                }
//                // write your code here
//                auto cur = head;
//                while (cur && cur->next) {
//                    auto tail = cur->next;
//                    auto prev = cur;
//                    while (tail->next) {
//                        prev = tail;
//                        tail = tail->next;
//                    }
//                    prev->next = nullptr;
//                    tail->next = cur->next;
//                    cur->next = tail;
//                    cur = cur->next->next;
//                }
                
            } // end reorderList
            
            
            RandomListNode *copyRandomList(RandomListNode *head) {
                
                if (!head) {
                    return head;
                }

                auto curt = head;
                while(curt) {
                    RandomListNode *copyNode = new RandomListNode(curt->label);
                    copyNode->next = curt->next;
                    curt->next = copyNode;
                    curt = curt->next->next;
                }
                
                curt = head;
                while (curt && curt->next) {
                    curt->next->random = (curt->random != nullptr) ? curt->random->next : nullptr;
                    curt = curt->next->next;
                }
                
                curt = head;
                auto newHead = head->next;
                auto p = newHead;
                
                while (curt) {
                    curt->next = p->next;
                    curt = curt->next;
                    p->next = curt != nullptr ? curt->next : curt;
                    p = p->next;
                }
                
                return newHead;
            } // end copyRandomList
            
            
        } // end namespace _LinkedList
        
        
    } // end _LintDataStructures
}