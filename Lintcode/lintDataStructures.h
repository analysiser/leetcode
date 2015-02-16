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
        
        
        // BST
        namespace _BSTPreorderTraversal {
            
            // recursion
            vector<int> recurPreorderTraversal(TreeNode *root);
            
            // stack
            vector<int> stackPreorderTraversal(TreeNode *root);
            
            // morris
            vector<int> morrisPreorderTraversal(TreeNode *root);
        }
        
        // BFS
        namespace _BFS {
            
            // 2 additional arrays BFS solution
            vector<vector<int>> levelOrderTwoArray(TreeNode *root);
            
            // 1 additional array BFS solution
            vector<vector<int>> levelOrderOneArray(TreeNode *root);
            
            // for bottom up version, just call reverse
            
            // zigzag level traversal
            vector<vector<int>> zigzagLevelOrder(TreeNode *root);
        }

        
    }
    
}

#endif /* defined(__Leetcode__lintDataStructures__) */
