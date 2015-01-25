//
//  leetHardA.cpp
//  Leetcode
//
//  Created by Xiao Li on 12/26/14.
//  Copyright (c) 2014 Xiao. All rights reserved.
//

#include "leetHardA.h"

namespace _hard {
    
    namespace _033 {
        // 33	Search in Rotated Sorted Array
        int search(int A[], int n, int target) {
            int l = 0;
            int r = n-1;
            while (l <= r) {
                int mid = (l + r)/2;
                if (A[mid] == target)   return mid;
                else if (A[l] <= A[mid]) {
                    if (A[l] <= target && target <= A[mid]) {
                        r = mid-1;
                    }
                    else {
                        l = mid+1;
                    }
                }
                else {
                    if (A[mid] <= target && target <= A[r]) {
                        l = mid+1;
                    }
                    else {
                        r = mid-1;
                    }
                }
            }
            return -1;
        }
    }
    
    namespace _004 {
        
        int partition(int A[], int m, int B[], int n, int left, int right, int pi) {
            int pivot = pi < m ? A[pi] : B[pi-m];
            int *pPivot = pi < m ? A+pi : B+pi-m;
            int *high = right < m ? A+right : B+right-m;
            std::swap(*high, *pPivot);
            int storeIndex = left;
            for (int i = left; i < right; i++) {
                int *v = i < m ? A+i : B+i-m;
                if (*v < pivot) {
                    int *storev = storeIndex < m ? A+storeIndex : B+storeIndex-m;
                    std::swap(*storev, *v);
                    storeIndex+=1;
                }
            }
            int *storev = storeIndex < m ? A+storeIndex : B+storeIndex-m;
            std::swap(*high, *storev);
            return storeIndex;
        }
        
        int select(int A[], int m, int B[], int n, int left, int right, int nth) {
            if (left == right) {
                return left < m ? A[left] : B[left-m];
            }
            int pivotIndex = left;
            pivotIndex = partition(A, m, B, n, left, right, pivotIndex);
            if (pivotIndex == nth)
                return nth < m ? A[nth] : B[nth-m];
            else if (pivotIndex < nth) {
                return select(A, m, B, n, pivotIndex+1, right, nth);
            }
            else {
                return select(A, m, B, n, left, pivotIndex-1, nth);
            }
        }
        
        double findMedianSortedArrays(int A[], int m, int B[], int n) {
            if (m+n == 0)
                return 0;
            bool needTwo = (m+n)%2 == 0;
            if (m == 0) {
                if (needTwo) {
                    return double(B[n/2] + B[n/2-1])/double(2);
                }
                else {
                    return B[n/2];
                }
            }
            if (n == 0) {
                if (needTwo) {
                    return double(A[m/2] + A[m/2-1])/double(2);
                }
                else {
                    return A[m/2];
                }
            }
            
            if (needTwo) {
                int v1 = select(A, m, B, n, 0, m+n-1, (m+n-1)/2);
                int v2 = select(A, m, B, n, 0, m+n-1, (m+n)/2);
                return double(v1+v2)/double(2);
            }
            else {
                return select(A, m, B, n, 0, m+n-1, (m+n)/2);
            }
        }
    }
    
    
    
    namespace _010 {
        
        // 10	Regular Expression Matching, Someone else's solution...
        bool isMatch(const char *s, const char *p) {
            if (!*p)    return (!*s);
            
            if ('*' == *(p + 1)) {
                // x* matches empty string or at least one character: x* -> xx*
                // *s is to ensure s is non-empty
                return (isMatch(s, p + 2) || (*s && (*s == *p || '.' == *p) && isMatch(s + 1, p)) );
            } else {
                if (!*s)    return false;
                return (*s == *p || '.' == *p) ? isMatch(s + 1, p + 1) : false;
            }
        }
    }
    
    namespace _025 {
        // 25   Reverse Nodes in k-Group
        ListNode *reverseKGroup(ListNode *head, int k) {
            
            int size = 0;
            auto tmp = head;
            while (tmp) {
                tmp = tmp->next;
                size++;
            }
            int times = size/k;
            if (size == 0 || times == 0 || k == 1)
                return head;
            
            ListNode *newhead = nullptr;
            for (int i = 0; i < times; i++) {
                int t = 0;
                auto cur = head;
                ListNode *prev = nullptr;
                while(t < k) {
                    auto tmp = cur;
                    cur = cur->next;
                    tmp->next = prev;
                    prev = tmp;
                    t++;
                }
                if (!newhead) {
                    newhead = prev;
                }
                if (i+1<times) {
                    tmp = cur;
                    for(int j = 1; j < k; j++) {
                        tmp=tmp->next;
                    }
                    head->next = tmp;
                    head = cur;
                }
                else {
                    head->next = cur;
                }
            }
            
            return newhead;
        }
    }
    
    
}

