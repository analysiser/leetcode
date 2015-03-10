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
        
        
        namespace _Subsets {
            // Subsets I
            void dfsHelper(vector<vector<int> > &results, vector<int> &aSol, vector<int> &nums, int num, int index) {
                if (aSol.size() == num) {
                    results.push_back(aSol);
                }
                else {
                    for (int i = index; i < nums.size(); i++) {
                        aSol.push_back(nums[i]);
                        dfsHelper(results, aSol, nums, num, i + 1);
                        aSol.pop_back();
                    }
                }
            }
            
            vector<vector<int> > subsets(vector<int> &nums) {
                // write your code here
                vector<vector<int> > results;
                
                int n = nums.size();
                for (int i = 0; i <= n; i++) {
                    vector<int> aSol;
                    dfsHelper(results, aSol, nums, i, 0);
                }
                
                return results;
            } // end subsets
            
            
            void dfsSubsetsWithDup(vector<vector<int> > &res,
                                   vector<int> &sol, vector<int> &A,
                                   int num, int index) {
                if (sol.size() == num) {
                    res.push_back(sol);
                }
                else {
                    for (int i = index; i < A.size(); i++) {
                        if (i != index && ( i > 0 && A[i] == A[i-1])) {
                            continue;
                        }
                        sol.push_back(A[i]);
                        dfsSubsetsWithDup(res, sol, A, num, i+1);
                        sol.pop_back();
                    }
                }
            }
            
            vector<vector<int> > subsetsWithDup(const vector<int> &S) {
                // write your code here
                vector<int> A(S.begin(), S.end());
                sort(A.begin(), A.end());
                vector<vector<int> > res;
                vector<int> sol;
                
                for (int k = 0; k <= A.size(); k++) {
                    dfsSubsetsWithDup(res, sol, A, k, 0);
                }
                return res;
            } // end subsetsWithDup
            
            
            
        } // end namespace _Subsets
        
        void partitionDfsHelper(string &s, vector<string> &sol, vector<vector<string> > &res, vector<vector<bool> > &f, int index) {
            if (index >= s.size()) {
                res.push_back(sol);
            }
            else {
                for (int i = index; i < s.size(); i++) {
                    if (f[index][i]) {
                        sol.push_back(s.substr(index, i - index + 1));
                        partitionDfsHelper(s, sol, res, f, i+1);
                        sol.pop_back();
                    }
                }
            }
        }
        
        
        vector<vector<string>> partition(string s) {
            int n = s.size();
            vector<bool> line(n, false);
            vector<vector<bool> > f(n, line);
            vector<vector<string> > ret;
            vector<string> sol;
            if (n == 0) {
                return ret;
            }
            
            for (int i = 0; i < n; i++) {
                f[i][i] = true;
            }
            
            for (int l = 2; l <= n; l++) {
                for (int i = 0; i < n - l + 1; i++) {
                    int j = i + l - 1;
                    if ((s[i] == s[j]) && !f[i][j]) {
                        f[i][j] = ((j-i == 1) || f[i+1][j-1]);
                    }
                }
            }
            
            partitionDfsHelper(s, sol, ret, f, 0);
            
            return ret;
        }
        
        
    }
    
}