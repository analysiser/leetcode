//
//  lintSearch.h
//  Leetcode
//
//  Created by Xiao Li on 2/9/15.
//  Copyright (c) 2015 Xiao. All rights reserved.
//

#ifndef __Leetcode__lintSearch__
#define __Leetcode__lintSearch__

#include <stdio.h>
#include "core.h"

using namespace std;


namespace _lintcode {
    
    // DFS, BFS, Permuation, Combination related problems
    namespace _LintSearch {
        
        // Permutation, find all permutations of array of non-duplicates
        // Without recursion version, used BFS
        vector<vector<int> > permute(vector<int> nums);
        
        // Find next of permution in ascending order with array of duplicates
        vector<int> nextPermuation(vector<int> &nums);
        
        // Find the previous permutation in ascending order with array with duplicates
        vector<int> previousPermuation(vector<int> &nums);
    }
    
}

#endif /* defined(__Leetcode__lintSearch__) */
