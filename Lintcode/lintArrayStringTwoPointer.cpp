//
//  lintArrayStringTwoPointer.cpp
//  Leetcode
//
//  Created by Xiao Li on 2/10/15.
//  Copyright (c) 2015 Xiao. All rights reserved.
//

#include "lintArrayStringTwoPointer.h"

namespace _lintcode {
    
    namespace _LintArrayStringTwoPointer {
        
        int singleNumberII(vector<int> &A) {
            
            int bits[32];
            fill_n(bits, 32, 0);
            for (int num : A) {
                for (int i = 0; i < 32; i++) {
                    if (num & (1 << i)) {
                        bits[i] += 1;
                    }
                }
            }
            
            int res = 0;
            for (int i = 0; i < 32; i++) {
                if (bits[i] % 3) {
                    res |= 1 << bits[i];
                }
            }
            
            return res;
        } // end singleNumberII
        
        
        vector<int> singleNumberIII(vector<int> &A) {
            int t = 0;
            for (const auto v : A) {
                t ^= v;
            }
            
            int mask = t & ~(t - 1); // mask for least significant bit
            int x = 0, y = 0;
            for (auto const v : A) {
                if (v & mask) {
                    x ^= v;
                }
                else {
                    y ^= v;
                }
            }
            
            vector<int> res = { x, y };
            return res;
            
        } // end singleNumberIII
        
        vector<vector<int> > threeSum(vector<int> &num) {
            
            vector<vector<int> > ret;
            if (num.size() < 3) return ret;
            
            map<int, int> lut;
            for (int v : num) {
                auto it = lut.find(v);
                if (it == lut.end()) {
                    lut.insert(make_pair(v, 1));
                }
                else {
                    it->second++;
                }
            }
            
            vector<int> keys;
            for (auto it = lut.begin(); it != lut.end(); it++) {
                keys.push_back(it->first);
            }
            
            for (int i = 0; i < keys.size(); i++) {
                int right = keys.size()-1;
                while (i <= right) {
                    int v1 = keys[i];
                    int v2 = keys[right];
                    int v3 = -(v1+v2);
                    if (v3 > v2) {
                        break;
                    }
                    else if (v3 < v1) {
                        right--;
                        continue;
                    }
                    else {
                        auto itv3 = lut.find(v3);
                        
                        if (itv3 != lut.end()) {
                            
                            auto itv1 = lut.find(v1);
                            auto itv2 = lut.find(v2);
                            
                            if (v3 <= v2 && v3 >= v1) {
                                itv1->second -= 1;
                                itv2->second -= 1;
                                itv3->second -= 1;
                                
                                if (itv1->second >= 0 && itv2->second >= 0 && itv3->second >= 0) {
                                    vector<int> asol = {v1, v3, v2};
                                    ret.push_back(asol);
                                    
                                }
                                itv1->second += 1;
                                itv2->second += 1;
                                itv3->second += 1;
                            }
                        }
                        
                        right--; 
                    }
                }
            }
            
            return ret;
//            // write your code here
//            vector<vector<int> > ret;
//            if (nums.size() < 3) {
//                return ret;
//            }
//            sort(nums.begin(), nums.end());
//            
//            for (int i = 0; i < nums.size() - 2; i++) {
//                if (i != 0 && nums[i] == nums[i-1]) {
//                    continue;
//                }
//                int left = i + 1;
//                int right = nums.size()-1;
//                while (left < right) {
//                    int sum = nums[i] + nums[left] + nums[right];
//                    if (sum == 0) {
//                        vector<int> asol = {nums[i], nums[left], nums[right]};
//                        ret.push_back(asol);
//                        left++;
//                        right--;
//                        while (left < right && nums[left] == asol[1]) {
//                            left++;
//                        }
//                        while (left < right && nums[right] == asol[2]) {
//                            right--;
//                        }
//                    }
//                    else if (sum < 0) {
//                        left++;
//                    }
//                    else {
//                        right--;
//                    }
//                }
//            }
//            
//            return ret;
        }
        
        string reverseWords(string s) {
            vector<string> tmp;
            for (int i = 0; i < s.size(); i++) {
                if (s[i] != ' ') {
                    int j = i+1;
                    while (j < s.size() && s[j] != ' ') {
                        j++;
                    }
                    tmp.push_back(s.substr(i, j-i));
                    i = j;
                }
            }
            
            string ret = "";
            if (tmp.size() == 0) {
                return ret;
            }
            reverse(tmp.begin(), tmp.end());
            for (int i = 0; i < tmp.size(); i++) {
                string ss = tmp[i];
                ret += ss + " ";
            }
            
            return ret.substr(0, ret.size()-1);
        }
    }
}