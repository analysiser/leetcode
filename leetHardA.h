//
//  leetHardA.h
//  Leetcode
//
//  Created by Xiao Li on 12/26/14.
//  Copyright (c) 2014 Xiao. All rights reserved.
//

#ifndef __Leetcode__leetHardA__
#define __Leetcode__leetHardA__

#include <stdio.h>
#include "core.h"


namespace _hard {
   
    namespace _033 {
        // 33	Search in Rotated Sorted Array : Binary search, Runtime 9 ms
        // Weirdly, O(n) solution could also pass the test cases
        int search(int A[], int n, int target);
    }
    
    namespace _004 {
        // 4	Median of Two Sorted Arrays : Quick Selection, 11 subs, 64 ms
        double findMedianSortedArrays(int A[], int m, int B[], int n);
    }
    
    
    namespace _010 {
        // 10	Regular Expression Matching
        bool isMatch(const char *s, const char *p);
    }
    
    namespace _025 {
        // 25   Reverse Nodes in k-Group : Linked List, annoying like hell, 3subs 29 ms
        ListNode *reverseKGroup(ListNode *head, int k);
    }
}


#endif /* defined(__Leetcode__leetHardA__) */
