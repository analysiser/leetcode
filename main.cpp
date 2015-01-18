//
//  main.cpp
//  Leetcode
//
//  Created by Xiao Li on 12/26/14.
//  Copyright (c) 2014 Xiao. All rights reserved.
//

#include <iostream>
#include "reference.hpp"
#include "testcases.h"

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
    
    TreeNode *node1 = new TreeNode(1);
    TreeNode *node2 = new TreeNode(2);
    TreeNode *node3 = new TreeNode(3);
    
    node3->left = node1;
    node1->right = node2;
    
    vector<int> res = preorderTraversal(node3);
    
    for (int v : res) {
        cout<<v<<endl;
    }
                           
    return 0;
}
