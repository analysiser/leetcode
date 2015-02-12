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

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    // Examples of debugging
    cout<<_hard::_044::isMatch("aaabababaaabaababbbaaaabbbbbbabbbbabbbabbaabbababab", "*a****************b")<<endl;
    
    vector<int> A = {232, 124, 456};
    cout<<_lintcode::_BinarySearch::woodCut(A, 7)<<endl;
    
    vector<int> num = {-1, 0, 1, 2, -1, -4};
    vector<vector<int>> res = _lintcode::_LintArrayStringTwoPointer::threeSum(num);
    for (auto vec : res) {
        for (int i = 0; i < vec.size(); i++) {
            cout<<vec[i]<<" ";
        }
        cout<<endl;
    
    }
    
    
    cout<<_lintcode::_LintArrayStringTwoPointer::reverseWords("the sky is blue")<<endl;

    
    return 0;
}


