//
//  leetHardA.cpp
//  Leetcode
//
//  Created by Xiao Li on 12/26/14.
//  Copyright (c) 2014 Xiao. All rights reserved.
//

#include "leetHardA.h"

namespace _hard {
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

