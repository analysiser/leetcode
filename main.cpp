//
//  main.cpp
//  Leetcode
//
//  Created by Xiao Li on 12/26/14.
//  Copyright (c) 2014 Xiao. All rights reserved.
//

#include <iostream>
#include <typeinfo>

#include "reference.hpp"
#include "testcases.h"


void print(char * mychar) {
    cout<<mychar<<endl;
    
}

class Base {
    virtual void f(){}
};

class Derived : public Base {
    
};

int xToPowerY(int base, int power) {
    if (power < 0) {
        return 0;
    }
    
    if (power == 0) {
        return 1;
    }
    
    int ret = 0;
    for (int i = 31; i >= 0; i--) {
        unsigned int p = 1 << i;
        if (p <= power) {
            ret |= base << p;
            power -= p;
        }
    }
    
    return ret;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
//    vector<vector<char> > a = {{'C','A','A'},{'A','A','A'},{'B','C','D'}};
//    std::cout<<exist(a, "AAB")<<endl;
    
//    int A[2] = {1, 3};
//    std::cout<<numDecodings("4757562545844617494555774581341211511296816786586787755257741178599337186486723247528324612117156948")<<endl;
    
//    vector<string> ret = restoreIpAddresses("010010");
//    cout<<ret.size()<<endl;
//    for (string s:ret) {
//        cout<<s<<endl;
//    }
//    TreeNode *node = new TreeNode(0);
//    vector<string> test = {"OXOOOX","OOXXXO","XXXXXO","OOOOXX","XXOOXO","OOXXXX"};
//    solve(test);
    
//    TreeNode *node1 = new TreeNode(1);
//    TreeNode *node2 = new TreeNode(2);
//    TreeNode *node3 = new TreeNode(3);
//    
//    node3->left = node1;
//    node1->right = node2;
//    
//    vector<int> res = preorderTraversal(node3);
//    
//    for (int v : res) {
//        cout<<v<<endl;
//    }
    
//    int A[3] = {-4, -3, -2};
//    cout<<maxProduct(A, 3)<<endl;
    
//    int a = INT_MIN;
//    int64_t aa = static_cast<int64_t>(a);
//    aa += INT_MIN;
//    std::cout<<aa<<std::endl;
//    
//    std::cout<<to_string(0.1250000000)<<std::endl;

//    vector<int> test = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//    cout<<largestNumber(test)<<endl;
    
//    int a[2] = {1, 1 };
//    int b[2] = {1, 1};
//    cout<<"solution = "<<_hard::_004::findMedianSortedArrays(a, 2, b, 2)<<" "<<endl;
    
//    const char *s = "aaa";
//    const char *p = "a*a";
//    cout<<_hard::_010::isMatch(s, p)<<endl;
    
//    string S = "barfoothefoobarman";
//    vector<string> L = {"foo", "bar"};
//    
//    vector<int> res = _hard::_030::findSubstring(S, L);
//    
//    for (int i : res) {
//        cout<<i<<endl;
//    }
    
//    cout<<_hard::_044::isMatch("aaabababaaabaababbbaaaabbbbbbabbbbabbbabbaabbababab", "*a****************b")<<endl;

//    vector<int> arr = {8,2,4,4,4,9,5,2,5,8,8,0,8,6,9,1,1,6,3,5,1,2,6,6,0,4,8,6,0,3,2,8,7,6,5,1,7,0,3,4,8,3,5,9,0,4,0,1,0,5,9,2,0,7,0,2,1,0,8,2,5,1,2,3,9,7,4,7,0,0,1,8,5,6,7,5,1,9,9,3,5,0,7,5};
//    
//    int *A = new int[arr.size()];
//    std::copy(arr.begin(), arr.end(), A);
//    cout<<_hard::_045::jump(A, arr.size())<<endl;
    
//    cout<<_hard::_076::minWindow("aa", "aa")<<endl;
    
//    vector<int> A = {0,0,0,0,0,0,0,0,2147483647};
//    cout<<_hard::_084::largestRectangleArea(A)<<endl;
    
//    cout<<xToPowerY(3, 2)<<endl;
    cout<<_hard::_087::isScramble("great", "rgeat")<<endl;
    

    
    return 0;
}


