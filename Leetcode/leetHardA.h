//
//  leetHardA.h
//  Leetcode
//
//  Created by Xiao Li on 12/26/14.
//  Copyright (c) 2014 Xiao. All rights reserved.
//

#ifndef __Leetcode__leetHardA__
#define __Leetcode__leetHardA__

#include <stdio.h>
#include "core.h"


namespace _hard {
    
    namespace _004 {
        // 4	Median of Two Sorted Arrays : Quick Selection, 11 subs, 64 ms
        double findMedianSortedArrays(int A[], int m, int B[], int n);
    }
    
    
    namespace _010 {
        // 10	Regular Expression Matching
        bool isMatch(const char *s, const char *p);
    }
    
    namespace _023 {
        // 23	Merge k Sorted Lists : Linked List, merge sort, DaC, 47 ms
        ListNode *mergeKLists(vector<ListNode *> &lists);
    }
    
    namespace _025 {
        // 25   Reverse Nodes in k-Group : Linked List, annoying like hell, 3subs 29 ms
        ListNode *reverseKGroup(ListNode *head, int k);
    }
    
    namespace _030 {
        // 30	Substring with Concatenation of All Words : Hashtable, 2 subs, 560 ms, so slow...
        // I figured out that I made this so complicated was because I didn't notice it says
        // all words in L are in same length... so my solution is more generic
        vector<int> findSubstring(string S, vector<string> &L);
    }
    
    namespace _032 {
        // 32	Longest Valid Parentheses : DP, string, 4 subs, 15 ms
        int longestValidParentheses(string s);
    }
    
    namespace _033 {
        // 33	Search in Rotated Sorted Array : Binary search, Runtime 9 ms
        // Weirdly, O(n) solution could also pass the test cases
        int search(int A[], int n, int target);
    }
    
    namespace _037 {
        // 37	Sudoku Solver : DFS, 1 sub, 176 ms
        void solveSudoku(vector<vector<char> > &board);
    }
    
    namespace _041 {
        // 41	First Missing Positive : Array used as storage, 6 ms
        int firstMissingPositive(int A[], int n);
    }
    
    namespace _042 {
        // 42   Trapping Rain Water : Array, 1 sub, 20 ms
        int trap(int A[], int n);
    }
    
    namespace _044 {
        // 44	Wildcard Matching : DP? Greedy? Not my solution
        // explain: http://yucoding.blogspot.com/2013/02/leetcode-question-123-wildcard-matching.html
        bool isMatch(const char *s, const char *p);
    }
    
    namespace _045 {
        // 45	Jump Game II : DP, 6 sub, 18 ms
        int jump(int A[], int n);
    }
    
    namespace _047 {
        // 47	Permutations II : DFS, 3 sub, 36 ms
        vector<vector<int> > permuteUnique(vector<int> &num);
    }
    
    namespace _051 {
        // 51	N-Queens : DFS, 4 subs, 20 ms
        vector<vector<string> > solveNQueens(int n);
    }
    
    namespace _052 {
        // 52	N-Queens II : DFS, 2 subs, 50 ms
        int totalNQueens(int n);
    }
    
    namespace _056 {
        // 56	Merge Intervals : Sort, 1 sub, 21 ms
        vector<Interval> merge(vector<Interval> &intervals);
    }
    
    namespace _057 {
        // 57	Insert Interval : Array, bounding box test, 1 sub, 18 ms
        vector<Interval> insert(vector<Interval> &intervals, Interval newInterval);
    }
    
    namespace _068 {
        vector<string> fullJustify(vector<string> & words, int L);
    }
    
    namespace _072 {
        // 72   Min Distance : I used DFS, 7 subs, 125 ms
        namespace _sol1 {
            int minDistance(string word1, string word2);
        }
        
        // 72 DP solution
        namespace _sol2 {
            int minDistance(string word1, string word2);
        }
    }
    
    namespace _154 {
        // 154	Find Minimum in Rotated Sorted Array II, 1 sub, 16 ms
        int findMin(vector<int> &num);
        
    }
    
    namespace _132 {
        // 132
        // Palindrome paritioning II
        int minCut(string s);
    }
    
    namespace _124 {
        
        // 124	Binary Tree Maximum Path Sum, DaC, 1 sub, 42 ms
        int maxPathSum(TreeNode *root);
    }
    
    namespace _128 {
        
        // 128  Longest Consecutive Sequence, make table, N sub, 30 ms
        int longestConsecutive(vector<int> &num);
        
    }
    
    namespace _138 {
        
        // 138  Copy List with Random Pointer, 119 ms, without hashtable
        // 144 ms, with hashtable, 1 sub, another solution is in lintDataStructures
        RandomListNode *copyRandomList(RandomListNode *head);
    }
    
    namespace _099 {
        // Recover Binary Search Tree, O(n) space, 5 sub, 78 ms
        void recoverTree(TreeNode *root);
    }
    
    namespace _099_2 {
        // Recover Binary Search Tree, O(1) space, morris, 3 sub, 67 ms
        void recoverTree(TreeNode *root);
    }
    
    namespace _140 {
        
        // 140	Word Break II
        vector<string> wordBreak(string s, unordered_set<string> &dict);
    }
    
}


#endif /* defined(__Leetcode__leetHardA__) */
