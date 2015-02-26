//
//  reference.hpp
//  Leetcode
//
//  Created by Xiao Li on 12/26/14.
//  Copyright (c) 2014 Xiao. All rights reserved.
//

#ifndef Leetcode_reference_hpp
#define Leetcode_reference_hpp

#include "Leetcode/leetEasy.h"

#include "Leetcode/leetMediumA.h"

#include "Leetcode/leetHardA.h"
#include "Leetcode/leetHardB.h"

#include "Lintcode/lintBinarySearch.h"
#include "Lintcode/lintArrayStringTwoPointer.h"
#include "Lintcode/lintDaC.h"
#include "Lintcode/lintDataStructures.h"
#include "Lintcode/lintDP.h"

// C style functions
int strcmp(const char *s1, const char *s2) {
    while (*s1 == *s2 && *s1) {
        s1++; s2++;
    }
    return *s1-*s2;
}

char *strtok(char *str, const char *delimiters) {
    static char *_buffer;
    if (str != NULL) {
        _buffer = str;
    }
    if (_buffer[0] == '\0') {
        return NULL;
    }
    
    char *ret = _buffer, *b;
    const char *d;
    
    for (b = _buffer; *b; b++) {
        for (d = delimiters; *d; d++) {
            if (*b == *d) {
                *b = '\0';
                _buffer = b+1;
                
                if (b == ret) {
                    continue;
                }
                return ret;
            }
        }
    }
    
    return ret;
}


void preorderTraversalHelper(TreeNode *node) {
    if (node) {
        preorderTraversalHelper(node->left);
        std::cout<<node->val<<std::endl;
        preorderTraversalHelper(node->right);
    }
}

#endif
