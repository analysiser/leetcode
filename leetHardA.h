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
   
    namespace _033 {
        // 33	Search in Rotated Sorted Array : Binary search, Runtime 9 ms
        // Weirdly, O(n) solution could also pass the test cases
        int search(int A[], int n, int target);
    }
    
    namespace _004 {
        // 4	Median of Two Sorted Arrays : Quick Selection, 11 subs, 64 ms
        double findMedianSortedArrays(int A[], int m, int B[], int n);
    }
    
    
    namespace _010 {
        // 10	Regular Expression Matching
        bool isMatch(const char *s, const char *p);
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
    
    namespace _037 {
        // 37	Sudoku Solver : DFS, 1 sub, 176 ms
        void solveSudoku(vector<vector<char> > &board);
    }
    
    namespace _041 {
        // 41	First Missing Positive : Array used as storage, 6 ms
        int firstMissingPositive(int A[], int n);
    }
}


#endif /* defined(__Leetcode__leetHardA__) */
