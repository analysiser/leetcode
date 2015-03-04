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
        
        // Recover Rotated Sorted Array
        // Given a rotated sorted array, recover it to sorted array in-place.
        // Challenge is to use O(1) space, O(n) time, 3-step-reverse
        void recoverRotatedSortedArray(vector<int> &nums);
        
        // Rotate String
        // Given a string and an offset, rotate string by offset. (rotate from left to right)
        // 3-step-revers
        string rotateString(string A, int offset);
        
        
        /****** Medium: direct binary search problems ******/
        // Search for a Range : 2 binary searches, find a range
        vector<int> searchRange(vector<int> &A, int target);
        
        // Search in a 2D matrix ii, but, the values increase in both row and col
        // there are no dupliates inside the same row or col, the matrix is not
        // incremental itself
        int searchMatrix2(vector<vector<int> > &matrix, int target);
        
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
        
        // Find median of unsored array
        int median(vector<int> &nums);
        
        
        /****** Hard: hard to think out ******/
        // Find median of two sorted array, with complexity of O(log(m+n))
        // I have another solution in leetcode part. That one uses kth-element selection
        // algorithm, this one is more like binary search. Due to the fact that
        // the arrays are alreayd sorted, binary search should run faster.
        double findMedianSortedArrays(vector<int> A, vector<int> B);

    }
    
}

#endif /* defined(__Leetcode__lintBinarySearch__) */
