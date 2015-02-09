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
        
        
        vector<int> searchRange(vector<int> &A, int target) {
            // write your code here
            vector<int> ret = {-1, -1};
            if ((A.size() == 0) || (target < A[0]) || (target > A[A.size()-1])) {
                return ret;
            }
            
            int start = 0, end = int(A.size()-1);
            while (start + 1 < end) {
                int mid = start + (end - start)/2;
                if (target <= A[mid]) {
                    end = mid;
                }
                else {
                    start = mid;
                }
            }
            
            if (A[end] == target) {
                ret[0] = end;
            }
            if (A[start] == target) {
                ret[0] = start;
            }
            
            start = 0;
            end = int(A.size()-1);
            while (start + 1 < end) {
                int mid = start + (end - start)/2;
                if (target >= A[mid]) {
                    start = mid;
                }
                else {
                    end = mid;
                }
            }
            
            if (A[start] == target) {
                ret[1] = start;
            }
            if (A[end] == target) {
                ret[1] = end;
            }
            
            return ret;
        }
        
        
        int findFirstBadVersion(int n) {
            // write your code here
            if (n < 0) {
                return n;
            }
            int l = 1, r = n;
            while (l+1 < r) {
                int mid = l + (r-l)/2;
                if (VersionControl::isBadVersion(mid)) {
                    r = mid;
                }
                else {
                    l = mid;
                }
            }
            
            if (VersionControl::isBadVersion(l)) {
                return l;
            }
            if (VersionControl::isBadVersion(r)) {
                return r;
            }
            return -1;
        }
        
        
        int search(vector<int> &A, int target) {
            // write your code here
            if (A.size() == 0) {
                return -1;
            }
            
            int l = 0, r = int(A.size()-1);
            while (l+1 < r) {
                int m = l + (r-l)/2;
                if (target == A[m]) {
                    return m;
                }
                // this if can be removed, but this way is clearer
                if (A[l] < A[r]) {
                    if (target < A[m]) {
                        r = m-1;
                    }
                    else {
                        l = m+1;
                    }
                }
                else {
                    if (A[m] > A[l]) {
                        if (target < A[m] && target >= A[l]) {
                            r = m-1;
                        }
                        else {
                            l = m+1;
                        }
                    }
                    else {
                        if (target <= A[r] && target > A[m]) {
                            l = m+1;
                        }
                        else {
                            r = m-1;
                        }
                    }
                }
            }
            if (target == A[l]) {
                return l;
            }
            if (target == A[r]) {
                return r;
            }
            return -1;
        }
        
        
        int findMin(vector<int> &num) {
            // write your code here
            int n = int(num.size());
            if (n == 0) {
                return -1;
            }
            
            int l = 0, r = n-1;
            while (l + 1 < r) {
                int m = l + (r-l)/2;
                if (num[m] >= num[r]) {
                    l = m + 1;
                }
                else {
                    r = m;
                }
            }
            if (num[l] < num[r]) {
                return num[l];
            }
            else {
                return num[r];
            }
        }
        
        
        /**
         *@param L: Given n pieces of wood with length L[i]
         *@param k: An integer
         *return: The maximum length of the small pieces.
         */
        int woodCut(vector<int> L, int k) {
            // write your code here
            if (L.size() == 0) {
                return 0;
            }
            
            int minLen = 0;
            int maxLen = L[0];
            for (int l : L) {
                if (l > maxLen) {
                    maxLen = l;
                }
            }
            
            int start = minLen;
            int end = maxLen;
            while (start+1 < end) {
                int mid = start + (end - start)/2;
                int count = 0;
                for (int l : L) {
                    count += l/mid;
                }
                if (count < k) {
                    end = mid;
                }
                else {
                    start = mid;
                }
            }
            
            
            if (end > 0) {
                int count = 0;
                for (int l : L) {
                    count += l/end;
                }
                if (count >= k) {
                    return end;
                }
            }
            
            if (start > 0) {
                int count = 0;
                for (int l : L) {
                    count += l/start;
                }
                if (count >= k) {
                    return start;
                }
                
            }
            
            return 0;

        }
        
        /**
         * @param A: An integers array.
         * @return: return any of peek positions.
         */
        int findPeak(vector<int> A) {
            // write your code here
            if (A.size() == 0) {
                return -1;
            }
            if (A.size() == 1) {
                return 0;
            }
            int l = 0, r = A.size()-1;
            while (l + 1 < r) {
                int mid = l + (r - l)/2;
                if ((A[mid-1] < A[mid])) {
                    if (A[mid+1] < A[mid]) {
                        return mid;
                    }
                    else {
                        l = mid;
                    }
                }
                else {
                    r = mid;
                }
            }
            if (A[l] > A[r]) {
                return l;
            }
            if (A[r] > A[l]) {
                return r;
            }
            return -1;
        }
        
        vector<int> mergeSortedArray(vector<int> &A, vector<int> &B) {
            // write your code here
            if (A.size() == 0) {
                return B;
            }
            if (B.size() == 0) {
                return A;
            }
            
            int ia = 0;
            int ib = 0;
            
            vector<int> C;
            C.reserve(A.size() + B.size());
            
            while((ia < A.size()) && (ib < B.size())) {
                int lena = 0;
                int lenb = 0;
                while (A[ia+lena] <= B[ib]) {
                    lena++;
                    if (ia + lena == A.size()) {
                        break;
                    }
                }
                if (lena > 0) {
                    C.insert(C.end(), A.begin() + ia, A.begin() + ia + lena);
                    ia += lena;
                }
                
                while ((ia < A.size()) && (ib+lenb < B.size()) && (A[ia] >= B[ib+lenb])) {
                    lenb++;
                    if (ib + lenb == B.size()) {
                        break;
                    }
                }
                if (lenb > 0) {
                    C.insert(C.end(), B.begin() + ib, B.begin() + ib + lenb);
                    ib += lenb;
                }
            }
            
            if (ia < A.size()) {
                C.insert(C.end(), A.begin() + ia, A.end());
            }
            if (ib < B.size()) {
                C.insert(C.end(), B.begin() + ib, B.end());
            }
            return C;
        }
        
        /**
         * @param A: sorted integer array A which has m elements,
         *           but size of A is m+n
         * @param B: sorted integer array B which has n elements
         * @return: void
         */
        void mergeSortedArray(int A[], int m, int B[], int n) {
            // write your code here
            if (n == 0) {
                return;
            }
            int i = m-1, j = n-1, k = m+n-1;
            while ((i >= 0) && (j >= 0)) {
                if (A[i] >= B[j]) {
                    A[k] = A[i];
                    i--;
                    k--;
                }
                else {
                    A[k] = B[j];
                    j--;
                    k--;
                }
            }
            if (j >= 0) {
                std::copy(B, B+j+1, A);
            }
        }
    }
}
