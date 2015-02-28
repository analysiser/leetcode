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
#include "experiments.h"

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

int main(int argc, const char * argv[]) {
//    // insert code here...
//    std::cout << "Hello, World!\n";
//    
//    string yeah = "parallel world!\n";
//    int result;
//    thread t1 {
//        printsomething, yeah, &result
//    };
//    
//    cout<<result<<endl;
//    
//    
//    
//    // Examples of debugging
//    cout<<_hard::_044::isMatch("aaabababaaabaababbbaaaabbbbbbabbbbabbbabbaabbababab", "*a****************b")<<endl;
//    
//    vector<int> A = {232, 124, 456};
//    cout<<_lintcode::_BinarySearch::woodCut(A, 7)<<endl;
//    
//    vector<int> num = {-1, 0, 1, 2, -1, -4};
//    vector<vector<int>> res = _lintcode::_LintArrayStringTwoPointer::threeSum(num);
//    for (auto vec : res) {
//        for (int i = 0; i < vec.size(); i++) {
//            cout<<vec[i]<<" ";
//        }
//        cout<<endl;
//    
//    }
//    
//    cout<<_lintcode::_LintArrayStringTwoPointer::reverseWords("the sky is blue")<<endl;
//    
//    int time = 20150215;
//    
//    std::stringstream ss;
//    
//    ss << time;
//    string test;
//    ss >> test;
//    
//    string year = test.substr(0, 4);
//    string month = test.substr(4, 2);
//    string day = test.substr(6, 2);
//    string ret = day + '/' + month + '/' + year;
//    cout<<ret<<endl;
//    
//    t1.join();
//    
//    cout<<_hard::_132::minCut("ab")<<endl;
//    
//    vector<int> range = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
//    _lintcode::_BinarySearch::searchRange(range, 5);
//    
//    vector<int> nums = {2147483646,-2147483647,0,2,2147483644,-2147483645,2147483645};
//    cout<<"128: "<<_hard::_128::longestConsecutive(nums)<<endl;
//    
//    ListNode *l1 = new ListNode(2);
//    ListNode *l2 = nullptr;
//    ListNode *l3 = new ListNode(-1);
//    vector<ListNode *> lists = {l1, l2, l3};
//    ListNode *ll = _lintcode::_LintDataStructures::_LinkedList::mergeKLists(lists);
//    
//    cout<<"!!!!!!!!!"<<endl;
//    auto p = ll;
//    while (p) {
//        cout<<p->val<<", ";
//        p = p->next;
//    }
//    
//    
//    cout<<endl<<"--- leetcode 99 ---"<<endl;
//    TreeNode *recoverRoot= new TreeNode(2);
//    recoverRoot->left = new TreeNode(3);
//    recoverRoot->right = new TreeNode(1);
//    
//    _hard::_099::recoverTree(recoverRoot);
//    
//    preorderTraversalHelper(recoverRoot);
//    
//    
//    cout<<"min cut"<<endl;
//    cout<<_lintcode::_DP::minCut("abcccb")<<endl;
//    
//    cout<<"subarraySum"<<endl;
//    vector<int> subarrayTest = {37,90,40,73,80,12,84,-2,43,82,31,91,-32,-5,23,48,37,-32,42,42,12,59,46,99,30,3,-39,31,48,26,-1,-22,49,20,-1,72,92,70,-26,8,29,11,-39,92,25,80,78,5,-46,-28,35,-15,-26,9,1,-23,55,94,47,6,57,67,93,-12,87,47,-12,-29,-7,-48,2,11,46,1,-50,59,39,-38,28,97,60,10,29,75,71,57,15,66,1,8,-22,23,19,35,48,50,95,59,-38,79,11,-6,67,66,-46,70,57,-3,41,72,94,-13,56,33,74,-46,22,61,70,-47,9,100,41,-25,62,82,60,67,36,73,8,50,69,52,16,14,86,-41,88,2,-25,16,-23,89,12,53,-46,-20,-5,8,-11,76,-27,60,-19,-3,53,11,10,-5,55,47,-49,-21,-10,7,-24,6,20,6,89,77,-1,-45,85,96,33,66,5,13,72,-6,32,50,87,-9,-43,29,84,96,70,86,76,42,48,3,75,-26,40,25,-9,-15,-48,38,32,78,61,43,-29,57,1,79,23,61,36,15,8,45,88,-8,-12,40,64,21,-28,-1,8,90,-44,75,-32,-20,93,98,97,29,75,26,-21,6,-34,91,49,79,-10,65,11,44,66,76,77,87,-27,-4,96,43,-12,29,58,25,35,-10,84,69,83,82,98,7,78,93,51,21,41,54,-48,-43,17,-48,-40,-20,4,72,-21,-8,-7,8,11,78,77,37,44,95,-17,52,71,3,-14,-6,29,-37,25,63,24,13,62,30,81,64,15,59,56,33,86,-4,96,-35,17,58,97,-38,36,-16,10,60,44,45,46,-37};
//
//    
//    ChronoTimer timer;
//    timer.begin();
//    vector<int> subarrayRes = _lintcode::_DP::subarraySum(subarrayTest);
//    timer.stop();
//    timer.PrintDuration();
    
    unordered_set<string> dict = {"cat", "cats", "and", "sand", "dog"};
    vector<string> result = _hard::_140::wordBreak("catsanddog", dict);
    for (const auto str : result) {
        cout<<str<<endl;
    }
    
//    _exp::expMain();
    

    
    return 0;
}





