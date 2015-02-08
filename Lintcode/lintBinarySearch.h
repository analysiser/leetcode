//
//  lintBinarySearch.h
//  Leetcode
//
//  Created by Xiao Li on 2/8/15.
//  Copyright (c) 2015 Xiao. All rights reserved.
//

#ifndef __Leetcode__lintBinarySearch__
#define __Leetcode__lintBinarySearch__

#include <stdio.h>
#include "core.h"

using namespace std;


namespace _lintcode {
    
    namespace _BinarySearch {
        
        // Binary search, find first position
        int binarySearch(vector<int> &array, int target);
        
        // Search Insert Position, find the position of target to insert
        int searchInsert(vector<int> &A, int target);
        
        // Search a 2D (sorted) Matrix, return find or not
        bool searchMatrix(vector<vector<int> > &matrix, int target);
        
        // Sqrt(x), binary search, pay attention to overflow
        int sqrt(int x);
        
        
    }
    
}

#endif /* defined(__Leetcode__lintBinarySearch__) */
