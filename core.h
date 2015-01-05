//
//  core.h
//  Leetcode
//
//  Created by Xiao Li on 12/26/14.
//  Copyright (c) 2014 Xiao. All rights reserved.
//

#ifndef __Leetcode__core__
#define __Leetcode__core__

#include <stdio.h>
#include <iostream>
#include <algorithm>

#include <map>
#include <set>
#include <stack>
#include <deque>

#include <unordered_map>
#include <unordered_set>

#include <vector>
#include <string>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


#endif /* defined(__Leetcode__core__) */
