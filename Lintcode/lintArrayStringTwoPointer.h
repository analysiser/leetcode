//
//  lintArrayStringTwoPointer.h
//  Leetcode
//
//  Created by Xiao Li on 2/10/15.
//  Copyright (c) 2015 Xiao. All rights reserved.
//

#ifndef __Leetcode__lintArrayStringTwoPointer__
#define __Leetcode__lintArrayStringTwoPointer__

#include <stdio.h>
#include "core.h"

using namespace std;

namespace _lintcode {
    
    namespace _LintArrayStringTwoPointer {
        
#pragma mark - Array 
        
        // Single Number II : Given 3*n + 1 numbers,
        // every numbers occurs triple times except one, find it.
        int singleNumberII(vector<int> &A);
        
        // Single Number III : Given 2*n + 2 numbers,
        // every numbers occurs twice except two, find them.
        vector<int> singleNumberIII(vector<int> &A);
        
        // Product of Array Exclude Itself
        vector<long long> productExcludeItself(vector<int> &nums);
        
#pragma mark - Two Pointers
        // 3 sum = 0
        vector<vector<int> > threeSum(vector<int> &nums);
        
        // Reverse Words in a String
        string reverseWords(string s);
        
        // 3 sum closest : n sum problems, reduce complexity by 1, remember to sort
        int threeSumClosest(vector<int> nums, int target);
    }
}

#endif /* defined(__Leetcode__lintArrayStringTwoPointer__) */
