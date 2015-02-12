//
//  leetEasy.h
//  Leetcode
//
//  Created by Xiao Li on 12/26/14.
//  Copyright (c) 2014 Xiao. All rights reserved.
//

#ifndef __Leetcode__leetEasy__
#define __Leetcode__leetEasy__

#include <stdio.h>
#include "core.h"

using namespace std;

namespace _easy {
    
    // 21	Merge Two Sorted Lists
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2);
    
    // 169 Majority Element: map
    int majorityElement(vector<int> &num);
    
    // 168	Excel Sheet Column Title: recursion
    string convertToTitle(int n);
    
    // 165	Compare Version Numbers: string
    int compareVersion(string version1, string version2);
    
    // 160	Intersection of Two Linked Lists : linked list
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB);
    
    // 155	Min Stack : maintain min stack, OOP, 15 ms
    class MinStack;
    
    // 102	Binary Tree Level Order Traversal : BFS
    // 107	Binary Tree Level Order Traversal II : BFS + stack
    vector<vector<int> > levelOrderBottom(TreeNode *root);
    
    // 38	Count and Say : string, 2 pointers
    string countAndSay(int n);
    
    // 28	Implement strStr() : string, KMP or 2 pointers
    int strStr(char *haystack, char *needle);
    
    // 14	Longest Common Prefix : string
    string longestCommonPrefix(vector<string> &strs);
    
    // 171	Excel Sheet Column Number
    int titleToNumber(string s);
    
}
#endif /* defined(__Leetcode__leetEasy__) */
