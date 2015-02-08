//
//  lintBinarySearch.cpp
//  Leetcode
//
//  Created by Xiao Li on 2/8/15.
//  Copyright (c) 2015 Xiao. All rights reserved.
//

#include "lintBinarySearch.h"


namespace _lintcode {
    
    namespace _BinarySearch {
        
        /**
         * @param nums: The integer array.
         * @param target: Target number to find.
         * @return: The first position of target. Position starts from 0.
         */
        int binarySearch(vector<int> &array, int target) {
            // write your code here
            int l = 0, r = (int)array.size()-1;
            while (l+1 < r) {
                int mid = l + (r-l)/2;
                if (target == array[mid]) {
                    r = mid;
                }
                else if (target < array[mid]) {
                    r = mid;
                }
                else {
                    l = mid;
                }
            }
            if (array[l] == target) {
                return l;
            }
            if (array[r] == target) {
                return r;
            }
            
            return -1;
        }
        
        
        int searchInsert(vector<int> &A, int target) {
            // write your code here
            if ((A.size() == 0) || (target < A[0])) {
                return 0;
            }
            if (target > A.back()) {
                return (int)A.size();
            }
            int l = 0, r = (int)A.size()-1;
            while (l + 1 < r) {
                int mid = l + (r-l)/2;
                if (target == A[mid]) {
                    return mid;
                }
                else if (target < A[mid]) {
                    r = mid;
                }
                else {
                    l = mid;
                }
            }
            if (target == A[l]) {
                return l;
            }
            if (target == A[r]) {
                return r;
            }
            return r;
        }
        
        
        /**
         * @param matrix, a list of lists of integers
         * @param target, an integer
         * @return a boolean, indicate whether matrix contains target
         */
        bool searchMatrix(vector<vector<int> > &matrix, int target) {
            // write your code here
            if (matrix.size() == 0) {
                return false;
            }
            if (matrix[0].size() == 0) {
                return false;
            }
            int m = matrix.size();
            int n = matrix[0].size();
            int top = 0, bot = m-1;
            while(top + 1 < bot) {
                int mid = top + (bot-top)/2;
                if (target == matrix[mid][0]) {
                    return true;
                }
                else if (target < matrix[mid][0]) {
                    bot = mid;
                }
                else {
                    top = mid;
                }
            }
            
            
            int row = top;
            if (target > matrix[bot][0]) {
                row = bot;
            }
            
            int l = 0, r = n-1;
            while (l+1 < r) {
                int mid = l + (r-l)/2;
                if (target == matrix[row][mid]) {
                    return true;
                }
                else if (target < matrix[row][mid]) {
                    r = mid;
                }
                else {
                    l = mid;
                }
            }
            if ((target == matrix[row][l]) || (target == matrix[row][r]) ) {
                return true;
            }
            return false;
        }
        
        /**
         * @param x: An integer
         * @return: The sqrt of x
         */
        int sqrt(int x) {
            // write your code here
            if (x <= 0) {
                return 0;
            }
            if (x == 1) {
                return 1;
            }
            int64_t l = 1, r = x/2+1;
            while (l + 1 < r) {
                int64_t m = l + (r-l)/2;
                if (int64_t(x) >= m * m) {
                    l = m;
                }
                else if (int64_t(x) < m * m) {
                    r = m;
                }
            }
            
            return l;
            
        }
    }
    
}
