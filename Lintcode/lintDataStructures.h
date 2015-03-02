//
//  lintDataStructures.h
//  Leetcode
//
//  Created by Xiao Li on 2/12/15.
//  Copyright (c) 2015 Xiao. All rights reserved.
//

#ifndef __Leetcode__lintDataStructures__
#define __Leetcode__lintDataStructures__

#include <stdio.h>
#include "core.h"

using namespace std;

namespace _lintcode {
    
    namespace _LintDataStructures {
        
#pragma mark - Stack
        /**** Stack ****/
        // Min Stack
        // Asked in bloomberg campus interview, round 2
        // 15 ms
        class MinStack {
        public:
            MinStack() {
                // do initialization if necessary
            }

            void push(int number) {
                // write your code here
                st.push(number);
                if (minst.empty()) {
                    minst.push(make_pair(number, 1));
                }
                else {
                    auto &minP = minst.top();
                    if (number == minP.first) {
                        minP.second += 1;
                    }
                    else if (number < minP.first) {
                        minst.push(make_pair(number, 1));
                    }
                }
            }
            
            int pop() {
                // write your code here
                int number = st.top();
                st.pop();
                if (!minst.empty()) {
                    if (number == minst.top().first) {
                        minst.top().second -= 1;
                        if (minst.top().second == 0) {
                            minst.pop();
                        }
                    }
                }
                return number;
            }
            
            int min() {
                // write your code here
                if (!minst.empty()) {
                    return minst.top().first;
                }
                return 0;
            }
            
        private:
            stack<int> st;
            stack<pair<int, int>> minst;
        };
        
#pragma mark - BST
        /**** BST ****/
        // BST traversal
        namespace _BSTTraversal {
            
            // preorder
            // recursion
            vector<int> recurPreorderTraversal(TreeNode *root);
            
            // stack
            vector<int> stackPreorderTraversal(TreeNode *root);
            
            // morris
            vector<int> morrisPreorderTraversal(TreeNode *root);
            
            // inorder
            // stack, hard, current pointer
            // idea: only push right children when current is null
            vector<int> stackInorderTraversal(TreeNode *root);
            
            // morris
            vector<int> morrisInorderTraversal(TreeNode *root);
            
            // postorder
            // stack, reverse of preorder stack
            vector<int> stackPostorderTraversal(TreeNode *root);
            
            // morris postorder is tricky... 
            
        }
        
        // BST BFS
        namespace _BFS {
            
            // 2 additional arrays BFS solution
            vector<vector<int>> levelOrderTwoArray(TreeNode *root);
            
            // 1 additional array BFS solution
            vector<vector<int>> levelOrderOneArray(TreeNode *root);
            
            // for bottom up version, just call reverse
            
            // zigzag level traversal
            vector<vector<int>> zigzagLevelOrder(TreeNode *root);
        }

        // insert node into BST, iterative
        TreeNode* insertNode(TreeNode* root, TreeNode* node);
        
        namespace _BSTIterator {
            
            // O(h) additional space solution
            class BSTIteratorOh {
                
            public:

                BSTIteratorOh(TreeNode *root);
                
                bool hasNext();
                
                TreeNode* next();
                
            private:
                stack<TreeNode *> st;
                
            };
            
            // O(1) additional space solution
            class BSTIteratorO1 {
                
            public:
                BSTIteratorO1(TreeNode *root);
                
                bool hasNext();
                
                TreeNode* next();
                
            private:
                TreeNode *cur;
            };
            
        } // end namespace _BSTIterator
        
        
        // Delete a node in BST, recursive
        // Reference: AVL Tree removal, in core.h
        namespace _BSTDeleteNode {
            
            TreeNode *findMin(TreeNode *p);
            
            TreeNode *removeMin(TreeNode *p);
        
            TreeNode* removeNode(TreeNode* root, int value);
            
        } // end namespace _BSTDeleteNode
        
        
#pragma mark - LinkedList
        namespace _LinkedList {
            
            // Remove Duplicates from Sorted List
            ListNode *deleteDuplicates(ListNode *head);
            
            // Remove Duplicates from Sorted List II
            ListNode *deleteDuplicates2(ListNode *head);
            
            // Reverse Linked List I, in place, O(n)
            ListNode *reverse(ListNode *head);
            
            // Reverse Linked List II, in place, O(n)
            ListNode *reverseBetween(ListNode *head, int m, int n);
            
            // Partition List, partition linked list by value x, in place, O(n)
            ListNode *partition(ListNode *head, int x);
            
            // Sort List
            ListNode *sortList(ListNode *head);
            
            // Reordered List
            void reorderList(ListNode *head);
            
            // Copy List with Random Pointer, deep copy a linked list
            RandomListNode *copyRandomList(RandomListNode *head);
            
            // Merge k sorted list, heap implementation
            ListNode *mergeKLists(vector<ListNode *> &lists);
            
            // Convert Sorted List to Binary Search Tree
            TreeNode *sortedListToBST(ListNode *head);
            
            // Nth to Last Node in List
            ListNode *nthToLast(ListNode *head, int n);
            
            // Remove Nth Node From End of List
            ListNode *removeNthFromEnd(ListNode *head, int n);
            
            // Linked List Cycle
            bool hasCycle(ListNode *head);
            
            // Linked List Cycle II
            ListNode *detectCycle(ListNode *head);
            
            // Add up of two linked lists
            ListNode *addLists(ListNode *l1, ListNode *l2);
            
            // Rotate List
            ListNode *rotateRight(ListNode *head, int k);
            
        } // end namespace _LinkedList
        
#pragma mark - Graph
        
        // Clone graph
        UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node);
    }
    
}

#endif /* defined(__Leetcode__lintDataStructures__) */
