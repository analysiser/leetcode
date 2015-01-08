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

// 50	Pow(x, n) : numeric binary search, Runtime: 16 ms
double pow(double x, int n);

// 53	Maximum Subarray : DP, Runtime: 17 ms
int maxSubArray(int A[], int n);

// 54	Spiral Matrix : Array ops, Runtime: 4 ms
vector<int> spiralOrder(vector<vector<int> > &matrix);

// 55	Jump Game : array, kindda DP, Runtime: 17 ms
// I thought it was DFS/BFS first, and got TLE...
bool canJump(int A[], int n);

// 59	Spiral Matrix II : Array ops, Runtime: 6 ms
vector<vector<int> > generateMatrix(int n);

// 60	Permutation Sequence : Math ? Runtime: 10 ms
string getPermutation(int n, int k);

// 61	Rotate List : Linked List, Runtime: 19 ms
ListNode *rotateRight(ListNode *head, int k);

// 63	Unique Paths II : DP, Runtime: 9 ms, I think I can use BFS too, but maybe LTE.
// Same logic with (62	 Unique Paths)
int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid);

// 64	Minimum Path Sum : DFS, Runtime: 24 ms
// 1st I used BFS, got MLE
// 2nd I used DFS, got TLE
// 3rd I used a look up table for saving repeated calculations, ACed with 24 ms
// Although I figured out ppl are using DP for solving this problem
int minPathSum(vector<vector<int> > &grid);

// 69	Sqrt(x) : Binary search, Runtime: 39 ms
int sqrt(int x);





#endif /* defined(__Leetcode__leetMediumA__) */
