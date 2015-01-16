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

// 73	Set Matrix Zeroes : array, I used hash table passed with 93 ms.
void setZeroes(vector<vector<int> > &matrix);
namespace _alternative {
    // 73's array only solution, 90 ms
    void setZeroes(vector<vector<int> > &matrix);
}

// 74	Search a 2D Matrix : Binary search, 20 ms
// I used two binary search, cause log(m) + log(n) time complexity
// If treat the 2-D matrix as a whole list, a binary search is log(mn) = log(m) + log(n), so it is the same
bool searchMatrix(vector<vector<int> > &matrix, int target);

// 75	Sort Colors : array ? 10ms
// I used 2*O(n) time, alternative ways are feasible
void sortColors(int A[], int n);

namespace _alternative {
    // 12 ms solution. Highest rank on leetcode
    void sortColors(int A[], int n);
}

// 77	Combinations : Combination DFS, 12 ms
vector<vector<int> > combine(int n, int k);

// 78	Subsets : Recusion, combination, 13 ms
vector<vector<int> > subsets(vector<int> &S);

// 79	Word Search : DFS, 138ms
bool exist(vector<vector<char> > &board, string word);

// 81	Search in Rotated Sorted Array II : Binary search, array, recursion, 11 ms
bool search(int A[], int n, int target);

// 82	Remove Duplicates from Sorted List II : Linked List, 15 ms
ListNode *deleteDuplicates(ListNode *head);

// 86	Partition List : Linked List
ListNode *partition(ListNode *head, int x);

// 89	Gray Code : Combination, Backtracing, annoying like hell, 8ms
vector<int> grayCode(int n);

// 90	Subsets II : Combination, Recursion, 14ms
vector<vector<int> > subsetsWithDup(vector<int> &S);

// 91	Decode Ways : DP, 5ms, took almost 1.5 hours...
// my recusion implementation got LTE
int numDecodings(string s);

// 92	Reverse Linked List II, Linked List, 4ms, annoying question
ListNode *reverseBetween(ListNode *head, int m, int n);

// 93	Restore IP Addresses, string, DFS, Edge cases, 9ms
vector<string> restoreIpAddresses(string s);

// 94	Binary Tree Inorder Traversal
// Solution 1: recursive, 6ms
vector<int> inorderTraversal(TreeNode *root);

namespace _alternative {
    // Solution 2: Iterative, Morris Traversal, 6 ms
    vector<int> inorderTraversal(TreeNode *root);
}

// 95	Unique Binary Search Trees II, DFS, 25ms
vector<TreeNode *> generateTrees(int n);

// 96	Unique Binary Search Trees, DP, Combinations, 1ms
int numTrees(int n);

// 98	Validate Binary Search Tree, Recursion, DFS, 22 ms
bool isValidBST(TreeNode *root);

// 103	Binary Tree Zigzag Level Order Traversal, BFS, 7ms
vector<vector<int> > zigzagLevelOrder(TreeNode *root);

// 105	Construct Binary Tree from Preorder and Inorder Traversal, DFS, Two pointers, 43 ms
TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder);

// 106	Construct Binary Tree from Inorder and Postorder Traversal, DFS, 43 ms
TreeNode *buildTree106(vector<int> &inorder, vector<int> &postorder);

namespace _alternative {
    // 106 Iterative solution, 27 ms
    TreeNode *buildTree106(vector<int> &inorder, vector<int> &postorder);
}

// 109	Convert Sorted List to Binary Search Tree, DFS, BST, 48 ms
TreeNode *sortedListToBST(ListNode *head);

namespace _alternative {
    // 109, iterative, O(n) solution, 38 ms
    TreeNode *dfsConstructBST(ListNode **list, int size);
}

// 114	Flatten Binary Tree to Linked List, Binary Tree, Morris Traversal?, 12 ms
void flatten(TreeNode *root);

// 116	Populating Next Right Pointers in Each Node, BFS, 28 ms
void connect(TreeLinkNode *root);
namespace _alternative {
    // 116, O(1) space iterative, BFS, 31 ms
    void connect(TreeLinkNode *root);
}

// 120	Triangle, DP, O(n) space solution, 11 ms
int minimumTotal(vector<vector<int> > &triangle);

// 122	Best Time to Buy and Sell Stock II, DP, Greedy, 14 ms
int maxProfit(vector<int> &prices);

// 127	Word Ladder, BFS, Graph, 1031 ms, TODO: too slow I think...
int ladderLength(string start, string end, unordered_set<string> &dict);

// 130	Surrounded Regions, BFS, too low...
void solve(vector<vector<char>> &board);

// 131	Palindrome Partitioning, DFS, 15 ms
vector<vector<string>> partition(string s);

#endif /* defined(__Leetcode__leetMediumA__) */
