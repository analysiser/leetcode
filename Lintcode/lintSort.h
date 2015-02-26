//
//  lintSort.h
//  Leetcode
//
//  Created by Xiao Li on 2/9/15.
//  Copyright (c) 2015 Xiao. All rights reserved.
//

#ifndef __Leetcode__lintSort__
#define __Leetcode__lintSort__

#include <stdio.h>
#include "core.h"

using namespace std;


namespace _lintcode {
    
    namespace _LintSort {
        
        // Remove Duplicates from Sorted Array
        int removeDuplicates(vector<int> &nums);
        
        // Remove Duplicates from Sorted Array II
        int removeDuplicates2(vector<int> &nums);
        
        // Merge two sorted array I
        vector<int> mergeSortedArray(vector<int> &A, vector<int> &B);
        
        // Merge two sorted array II : not creating new spaces, but copy to A
        void mergeSortedArray(int A[], int m, int B[], int n);
        
        
        
        
    } // end namespace _LintSort
    
}

#endif /* defined(__Leetcode__lintSort__) */
