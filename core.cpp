//
//  core.cpp
//  Leetcode
//
//  Created by Xiao Li on 12/26/14.
//  Copyright (c) 2014 Xiao. All rights reserved.
//

#include "core.h"

AVLNode * AVLTree::insert(AVLNode *p, int val) {
    if (!p) {
        return new AVLNode(val);
    }
    if (val < p->val) {
        p->left = insert(p->left, val);
    }
    else {
        p->right = insert(p->right, val);
    }
    return balance(p);
}

AVLNode *AVLTree::findmin(AVLNode *p) {
    return p->left ? findmin(p->left) : p;
}

AVLNode *AVLTree::removemin(AVLNode *p) {
    if (!p->left) {
        return p->right;
    }
    p->left = removemin(p->left);
    return balance(p);
}

AVLNode * AVLTree::remove(AVLNode *p, int val) {
    if (!p) {
        return nullptr;
    }
    if (val < p->val) {
        p->left = remove(p->left, val);
    }
    else if (val > p->val) {
        p->right = remove(p->right, val);
    }
    else {
        auto q = p->left;
        auto r = p->right;
        delete p;
        if (!r) {
            return q;
        }
        AVLNode *min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    
    return balance(p);
}

AVLNode *AVLTree::rotateRight(AVLNode *p) {
    // update pointer
    AVLNode *q = p->left;
    p->left = q->right;
    q->right = p;

    // update height
    fixheight(p);
    fixheight(q);
    
    return q;
}

AVLNode *AVLTree::rotateLeft(AVLNode *p) {
    // update pointer
    AVLNode *q = p->right;
    p->right = q->left;
    q->left = p;
    
    // update height
    fixheight(p);
    fixheight(q);
    
    return q;
}

AVLNode *AVLTree::balance(AVLNode *p) {
    fixheight(p);
    if (bfactor(p) == 2) {
        if (bfactor(p->right) < 0) {
            p->right = rotateRight(p->right);
        }
        return rotateLeft(p);
    }
    else if (bfactor(p) == -2) {
        if (bfactor(p->left) > 0) {
            p->left = rotateLeft(p->left);
        }
        return rotateRight(p);
    }
    // no balance needed
    return p;
}