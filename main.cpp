//
//  main.cpp
//  Leetcode
//
//  Created by Xiao Li on 12/26/14.
//  Copyright (c) 2014 Xiao. All rights reserved.
//

#include "core.h"
#include "reference.hpp"
#include "testcases.h"

mutex m;

void printsomething(string s, int *res) {
    
    lock_guard<mutex> lck{m};
    cout<<s<<endl;
    for (int i = 0; i < 20; i++) {
        cout<<i<<endl;
    }
    *res = 42;
    // release mutex implicitly
}

const int kTotalTime = 300;
int logs[kTotalTime];
int lastTime = -1;

void log_hits(int t) {
    if (lastTime == -1) {
        lastTime = t;
    }
    else {
        if (t - lastTime > kTotalTime) {
            fill_n(logs, kTotalTime, 0);
            lastTime = t;
        }
    }
    logs[t%kTotalTime] += 1;
}

int get_hits_five_min() {
    int count = 0;
    for (int i = 0; i < kTotalTime; i++) {
        count += logs[i];
    }
    return count;
}

int strcmp1(const char *s1, const char *s2) {
    while ((*s1 == *s2) && (*s1)) {
        ++s1;
        ++s2;
    }
    return *s1-*s2;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    string yeah = "parallel world!\n";
    int result;
    thread t1 {
        printsomething, yeah, &result
    };
    
    cout<<result<<endl;
    
    
    
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
    
    int time = 20150215;
    
    std::stringstream ss;
    
    ss << time;
    string test;
    ss >> test;
    
    string year = test.substr(0, 4);
    string month = test.substr(4, 2);
    string day = test.substr(6, 2);
    string ret = day + '/' + month + '/' + year;
    cout<<ret<<endl;
    
    t1.join();
    
    cout<<_hard::_132::minCut("ab")<<endl;
    
    vector<int> range = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    _lintcode::_BinarySearch::searchRange(range, 5);
    
    
    return 0;
}





