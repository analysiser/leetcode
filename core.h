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
#include <sstream>

#include <algorithm>

#include <chrono>
#include <typeinfo>
#include <memory>
#include <thread>
#include <time.h>


#include <deque>
#include <map>
#include <queue>
#include <set>
#include <stack>


#include <unordered_map>
#include <unordered_set>

#include <vector>
#include <string>

#include <cassert>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};

struct DirectedGraphNode {
    int label;
    vector<DirectedGraphNode *> neighbors;
    DirectedGraphNode(int x) : label(x) {};
};

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) { }
    Interval(int s, int e) : start(s), end(e) { }
};

class VersionControl {
public:
    // definition to silence compiler
    static bool isBadVersion(int k) {
        return true;
    }
};

struct AVLNode {
    int val;
    unsigned char height;       //!< height is bottom up height
    AVLNode *left;
    AVLNode *right;
    AVLNode(int v) {
        val = v;
        left = nullptr;
        right = nullptr;
        height = 0;
    }
};

class AVLTree {
public:
    AVLTree() { root = nullptr; }
    AVLNode * insert(AVLNode *p, int val);
    AVLNode * remove(AVLNode *p, int val);
    
    static unsigned char height(AVLNode *p) {
        return p ? p->height : 0;
    }
    
    static int bfactor(AVLNode *p) {
        return height(p->right) - height(p->left);
    }
    
    static void fixheight(AVLNode *p) {
        auto lh = height(p->left);
        auto rh = height(p->right);
        p->height = (lh > rh ? lh : rh) + 1;
    }
    
    // rotate right
    AVLNode *rotateRight(AVLNode *p);
    
    // rotate left
    AVLNode *rotateLeft(AVLNode *p);
    
    // balance operation
    AVLNode *balance(AVLNode *p);
    
    // find min val node in AVL tree
    AVLNode *findmin(AVLNode *p);
    
    // remove the min value of tree
    AVLNode *removemin(AVLNode *p);
    
//private:
    AVLNode *root;
};


class ChronoTimer {
public:
    ChronoTimer() { }
    void begin() {
       start_ = std::chrono::high_resolution_clock::now();
    }
    
    void stop() {
        end_ = std::chrono::high_resolution_clock::now();
    }
    
    void PrintDuration() {
        auto duration = end_ - start_;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        std::cout<<"duration = "<<ms<<std::endl;
    }
    
private:
    
    std::chrono::steady_clock::time_point start_;
    std::chrono::steady_clock::time_point end_;
};


#endif /* defined(__Leetcode__core__) */
