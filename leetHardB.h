//
//  leetHardB.h
//  Leetcode
//
//  Created by Xiao Li on 2/6/15.
//  Copyright (c) 2015 Xiao. All rights reserved.
//

#ifndef __Leetcode__leetHardB__
#define __Leetcode__leetHardB__

#include <stdio.h>
#include "core.h"

namespace _hard {
    
    namespace _076 {
        // 76	Minimum Window Substring : 2 pointers, string, 12 ms, NOT MY SOLUTION
        // hashtable is really tricky on this, i got either TLE or MLE
        string minWindow(string S, string T);
    }
    
    namespace _084 {
        // 84	Largest Rectangle in Histogram : Stack O(n), NOT MY SOLUTION
        // devide and conquer : O(nlogn)
        // naive : O(n^2)
        int largestRectangleArea(vector<int> &height);
        
    }
    
    namespace _085 {
        // 85	Maximal Rectangle : DP, NOT MY SOLUTION
        int maximalRectangle(vector<vector<char>> &matrix);
    }
    
    namespace _087 {
        // 87	Scramble String : DP, NOT MY SOLUTION, explain:
        // http://blog.csdn.net/pickless/article/details/11501443
        bool isScramble(string s1, string s2);
    }
    
}

#endif /* defined(__Leetcode__leetHardB__) */
