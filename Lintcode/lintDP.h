//
//  lintDP.h
//  Leetcode
//
//  Created by Xiao Li on 2/23/15.
//  Copyright (c) 2015 Xiao. All rights reserved.
//

#ifndef __Leetcode__lintDP__
#define __Leetcode__lintDP__

#include <stdio.h>
#include "core.h"

namespace _lintcode {
    
    namespace _DP {
        
#pragma mark - Matrix
        // Matrix DP
        // Triangle numbers
        int minimumTotal(vector<vector<int> > &triangle);
        
        // Minimum Path Sum of a mxn matrix
        int minPathSum(vector<vector<int> > &grid);
        
        // Unique Paths : from top-left to bottom-right, how many unique paths
        int uniquePaths(int m, int n);
        
        // Unique Paths II : with obstacles
        int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid);
        
        
#pragma mark - Sequence
        // Climbing Stairs
        int climbStairs(int n);
        
        // Jump game, judge if can jump
        bool canJump(vector<int> A);
        
        // Jump Game II
        int jump(vector<int> A);
        
        // Palindrome Partitioning II
        int minCut(string s);
        
        
        vector<int> subarraySum(vector<int> nums);
        
        // Word Segmentation: tell if s can be segmented to words in dict
        bool wordSegmentation(string s, unordered_set<string> &dict);
    }
    
} // end namespace _lintcode


#endif /* defined(__Leetcode__lintDP__) */
