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
    
    // Problems mostly with in Binary Search Category
    namespace _BinarySearch {
        
        /****** Easy: direct binary search problems ******/
        // Binary search, find first position
        int binarySearch(vector<int> &array, int target);
        
        // Search Insert Position, find the position of target to insert
        int searchInsert(vector<int> &A, int target);
        
        // Search a 2D (sorted) Matrix, return find or not
        bool searchMatrix(vector<vector<int> > &matrix, int target);
        
        // Sqrt(x), binary search, pay attention to overflow
        int sqrt(int x);
        
        
        /****** Medium: direct binary search problems ******/
        // Search for a Range : 2 binary searches, find a range
        vector<int> searchRange(vector<int> &A, int target);
        
        // Find first bad version
        int findFirstBadVersion(int n);
        
        // Search in Rotated Sorted Array
        // Search in Rotated Sorted Array II: would lead to best complexity to be O(n)
        int search(vector<int> &A, int target);
        
        // Find Minimum in Rotated Sorted Array
        // Find Minimum in Rotated Sorted Array II: similar idea, O(n) solution
        int findMin(vector<int> &num);
        
        // Wood cut, annoying binary search, with /0 edge cases
        int woodCut(vector<int> L, int k);
        
        // Search for mid, when mid has 4 states
        int findPeak(vector<int> A);
        
        // Merge two sorted array I
        vector<int> mergeSortedArray(vector<int> &A, vector<int> &B);
        
        // Merge two sorted array II : not creating new spaces, but copy to A
        void mergeSortedArray(int A[], int m, int B[], int n);
    }
    
}

#endif /* defined(__Leetcode__lintBinarySearch__) */
