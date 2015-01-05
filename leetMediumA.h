//
//  leetMediumA.h
//  Leetcode
//
//  Created by Xiao Li on 12/26/14.
//  Copyright (c) 2014 Xiao. All rights reserved.
//

#ifndef __Leetcode__leetMediumA__
#define __Leetcode__leetMediumA__

#include <stdio.h>
#include "core.h"

using namespace std;

// 5    Longest Palindromic Substring : string, two pointers, inside out, 
string longestPalindrome(string s);
string longestPalindrome2(string s);

// 18	4Sum : array
vector<vector<int> > fourSum(vector<int> &num, int target);

// 71	Simplify Path : DP? queue
string simplifyPath(string path);

// 22	Generate Parentheses : DFS
vector<string> generateParenthesis(int n);

// 29	Divide Two Integers : binary search, bit ops
int divide(int dividend, int divisor);

// 31	Next Permutation : array, permutation
void nextPermutation(vector<int> &num);

// 34	Search for a Range : binary search
vector<int> searchRange(int A[], int n, int target);

// 39	Combination Sum : combination
vector<vector<int> > combinationSum(vector<int> &candidates, int target);

// 40   Combination Sum II
vector<vector<int> > combinationSum2(vector<int> &num, int target);

// 43	Multiply Strings
string multiply(string num1, string num2);  // string
string multiply2(string num1, string num2); // 2 pointers

// 46	Permutations : DFS
vector<vector<int> > permute(vector<int> &num);

// 48	Rotate Image : array
void rotate(vector<vector<int> > &matrix); // O(n^2) space
void rotate2(vector<vector<int> > &matrix); // in-place

// 49	Anagrams : hashtable, Runtime: 59 ms
vector<string> anagrams(vector<string> &strs);

#endif /* defined(__Leetcode__leetMediumA__) */
