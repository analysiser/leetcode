//
//  lintSort.cpp
//  Leetcode
//
//  Created by Xiao Li on 2/9/15.
//  Copyright (c) 2015 Xiao. All rights reserved.
//

#include "lintSort.h"

namespace _lintcode {
    
    namespace _LintSort {
        
        int removeDuplicates(vector<int> &num) {
            // write your code here
            if (num.size() < 2) {
                return static_cast<int>(num.size());
            }
            
            int size = 0;
            for (int i = 0; i < num.size(); i++) {
                if (num[i] != num[size]) {
                    num[++size] = num[i];
                }
            }
            return size + 1;
        } // end removeDuplicates
        
        
        int removeDuplicates2(vector<int> &nums) {
            // write your code here
            if (nums.size() < 3) {
                return nums.size();
            }
            
            int size = 0;
            int cnt = 0;
            for (int i = 1; i < nums.size(); i++) {
                if (nums[i] != nums[size]) {
                    nums[++size] = nums[i];
                    cnt = 0;
                }
                else {
                    if (cnt < 1) {
                        nums[++size] = nums[i];
                        cnt += 1;
                    }
                }
            }
            
            return size+1;
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
        
    } // end namespace _LintSort
    
}