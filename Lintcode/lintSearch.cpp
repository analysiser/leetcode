//
//  lintSearch.cpp
//  Leetcode
//
//  Created by Xiao Li on 2/9/15.
//  Copyright (c) 2015 Xiao. All rights reserved.
//

#include "lintSearch.h"

namespace _lintcode {
    
    namespace _LintSearch {
        
        /**
         * @param nums: A list of integers.
         * @return: A list of permutations.
         */
        vector<vector<int> > permute(vector<int> nums) {
            // write your code here
            vector<vector<int>> ret;
            if (nums.size() == 0) {
                return ret;
            }
            
            vector<vector<int>> next;
            vector<vector<int>> tmp;
            next.push_back(nums);
            for (int i = 1; i < nums.size(); i++) {
                for (vector<int> res : next) {
                    ret.push_back(res);
                    for (int j = 0; j < res.size(); j++) {
                        if (j + i >= res.size()) {
                            break;
                        }
                        else {
                            vector<int> cur = res;
                            swap(cur[j], cur[j+i]);
                            tmp.push_back(cur);
                        }
                    }
                }
                next.clear();
                next = tmp;
                tmp.clear();
            }
            
            return ret;
            
        }
        
        
        /**
         * @param nums: An array of integers
         * @return: An array of integers that's next permuation
         */
        vector<int> nextPermuation(vector<int> &nums) {
            // write your code here
            if (nums.size() == 0) {
                return nums;
            }
            
            int l = nums.size()-2;
            for (; l >= 0; l--) {
                if (nums[l] < nums[l+1]) {
                    break;
                }
            }
            
            if (l >= 0) {
                int r = nums.size()-1;
                for (; r > l; r--) {
                    if (nums[l] < nums[r]) {
                        swap(nums[l], nums[r]);
                        break;
                    }
                }
            }
            
            reverse(nums.begin() + l + 1, nums.end());
            return nums;
        }
        
        
        /**
         * @param nums: An array of integers
         * @return: An array of integers that's previous permuation
         */
        vector<int> previousPermuation(vector<int> &nums) {
            // write your code here
            if (nums.size() == 0) {
                return nums;
            }
            
            int l = nums.size() - 2;
            for (; l >= 0; l--) {
                if (nums[l] > nums[l+1]) {
                    break;
                }
            }
            
            if (l >= 0) {
                
                int r = nums.size() - 1;
                for (; r > l; r--) {
                    if (nums[r] < nums[l]) {
                        break;
                    }
                }
                swap(nums[l], nums[r]);
            }
            reverse(nums.begin() + l + 1, nums.end());
            return nums;
        }
        
    }
    
}