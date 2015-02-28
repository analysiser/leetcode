//
//  lintDP.cpp
//  Leetcode
//
//  Created by Xiao Li on 2/23/15.
//  Copyright (c) 2015 Xiao. All rights reserved.
//

#include "lintDP.h"

namespace _lintcode {
    
    namespace _DP {
        
        // bottom-up DP, matrix DP.
        int minimumTotal(vector<vector<int> > &triangle) {
            // write your code here
            if (triangle.size() == 0 || triangle[0].size() == 0) {
                return 0;
            }
            if (triangle.size() == 1) {
                return triangle[0][0];
            }
            
            for (int i = triangle.size()-2; i >= 0; i--) {
                for (int j = 0; j < triangle[i].size(); j++) {
                    triangle[i][j] = min(triangle[i+1][j], triangle[i+1][j+1]) + triangle[i][j];
                }
            }
            
            return triangle[0][0];
        } // end minimumTotal
        
        // Matrix DP, top-bottom
        int minPathSum(vector<vector<int> > &grid) {
            if (grid.size() == 0 || grid[0].size() == 0) {
                return 0;
            }
            
            int m = grid.size();
            int n = grid[0].size();
            
            // init
            vector<int> line(n, 0);
            vector<vector<int> > f(m, line);
            
            f[0][0] = grid[0][0];
            
            for (int i = 1; i < n; i++) {
                f[0][i] = grid[0][i] + f[0][i-1];
            }
            for (int j = 1; j < m; j++) {
                f[j][0] = grid[j][0] + f[j-1][0];
            }
            
            for (int i = 1; i < m; i++) {
                for (int j = 1; j < n; j++) {
                    f[i][j] = min(f[i-1][j], f[i][j-1]) + grid[i][j];
                }
            }
            
            return f[m-1][n-1];
        } // end minPathSum
        
        //
        int uniquePaths(int m, int n) {
            // wirte your code here
            if ((m == 0) || (n == 0)) {
                return 0;
            }
            if ((m == 1) || (n == 1)) {
                return 1;
            }
            
            // to save space lol
            if (m < n) {
                return uniquePaths(n, m);
            }
            
            // n space
            int path[n];
            fill_n(path, n, 1);
            for (int i = 1; i < m; i++) {
                for (int j = 1; j < n; j++) {
                    path[j] += path[j-1];
                }
            }
            
            return path[n-1];
            
            // mxn space
//            int f[m][n];
//            for (int i = 0; i < m; i++) {
//                f[i][0] = 1;
//            }
//            for (int j = 0; j < n; j++) {
//                f[0][j] = 1;
//            }
//            
//            for (int i = 1; i < m; i++) {
//                for (int j = 1; j < n; j++) {
//                    f[i][j] = f[i-1][j] + f[i][j-1];
//                }
//            }
//            
//            return f[m-1][n-1];
        } // end
        
        int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
            if (obstacleGrid.size() == 0 || obstacleGrid[0].size() == 0) {
                return 0;
            }
            
            int m = obstacleGrid.size();
            int n = obstacleGrid[0].size();
            
            int f[m][n];
            f[0][0] = obstacleGrid[0][0] ? 0 : 1;
            for (int i = 1; i < m; i++) {
                f[i][0] = obstacleGrid[i][0] ? 0 : f[i-1][0];
            }
            for (int j = 1; j < n; j++) {
                f[0][j] = obstacleGrid[0][j] ? 0 : f[0][j-1];
            }
            
            for (int i = 1; i < m; i++) {
                for (int j = 1; j < n; j++) {
                    f[i][j] = obstacleGrid[i][j] ? 0 : f[i][j-1] + f[i-1][j];
                }
            }
            
            return f[m-1][n-1];
            
        } // end uniquePathsWithObstacles
        
        
        // Climb stairs
        int climbStairs(int n) {
            if (n < 2) {
                return n;
            }
            
            int s[n+1];
            s[0] = 1;
            s[1] = 1;
            for (int i = 2; i <= n; i++) {
                s[i] = s[i-1] + s[i-2];
            }
            
            return s[n];
            
        } // end climbStairs
        
        
        bool canJump(vector<int> A) {
            // write you code here
            int n = A.size();
            if (n == 0) {
                return false;
            }
            if (n == 1) {
                return true;
            }
            int far = A[0];
            for (int i = 1; i < n; i++) {
                if (i > far) {
                    break;
                }
                int end = i + A[i];
                if (end >= n-1) {
                    return true;
                }
                if (end > far) {
                    far = end;
                }
            }
            return false;
        } // end canJump
        
        
        int jump(vector<int> A) {
            
            // greedy
            if (A.size() == 0) {
                return 0;
            }
            
            int n = static_cast<int>(A.size());
            int s[n];
            fill_n(s, n, INT_MAX);
            s[0] = 0;
            
            int front = 0;
            for (int i = 0; i < n; i++) {
                int end = i + A[i];
                if (end > front) {
                    end = end < n ? end : n-1;
                    fill_n(s + front + 1, end - front, s[i] + 1);
                    if (end == n-1) {
                        break;
                    }
                    front = end;
                }
            }
            
            return s[n-1];
            
            // DP
//            if (A.size() == 0) {
//                return 0;
//            }
//            
//            int n = static_cast<int>(A.size());
//            int s[n];
//            fill_n(s, n, INT_MAX);
//            s[0] = 0;
//            
//            for (int i = 1; i < n; i++) {
//                for (int j = 0; j < i; j++) {
//                    if ((s[j] + 1 < s[i]) && (j + A[j] >= i)) {
//                        s[i] = s[j] + 1;
//                    }
//                }
//            }
//            
//            return s[n-1];
        } // end jump
        
        
        int minCut(string s) {
            
            if (s.size() < 2) {
                return 0;
            }
            
            int n = s.size();
            int f[n + 1];
            for (int i = 0; i < n+1; i++) {
                f[i] = i - 1;
            }
            
            bool lut[n][n];
            memset(lut, 0, sizeof(bool) * n * n);
            for (int i = 0; i < n - 1; i++) {
                lut[i][i] = true;
                lut[i][i+1] = s[i] == s[i+1];
            }
            lut[n-1][n-1] = true;
            
            for (int l = 2; l <= n; l++) {
                for (int i = 0; i < n; i++) {
                    int j = i + l - 1;
                    if (j > n - 1) {
                        break;
                    }
                    if ((s[i] == s[j]) && lut[i+1][j-1]) {
                        lut[i][j] = true;
                    }
                }
            }
            
            for (int i = 1; i <= n; i++) {
                for (int j = 0; j < i; j++) {
                    if ((f[j] + 1 < f[i]) && lut[j][i-1]) {
                        f[i] = f[j] + 1;    
                    }
                }
            }
            
            return f[n];
            
        } // end minCut aka Palindrom Partitioning II
        
        
        vector<int> subarraySum(vector<int> nums) {
//            vector<int> res;
//            int n = nums.size();
//            
//            vector<int> line(n, 0);
//            vector<vector<int> > sums(n, line);
//            
//            for (int i = 0; i < n; i++) {
//                sums[i][i] = nums[i];
//                if (sums[i][i] == 0) {
//                    res = {i, i};
//                    return res;
//                }
//            }
//            
//            for (int l = 2; l <= n; l++) {
//                for (int i = 0; i < n - l + 1; i++) {
//                    int j = i + l - 1;
//                    sums[i][j] = sums[i][j-1] + nums[j];
//                    if (sums[i][j] == 0) {
//                        res = {i, j};
//                        return res;
//                    }
//                }
//            }
//            
//            return res;
            
            vector<int> res;
            
            for (int i = 0; i < nums.size(); i++) {
                int sum = 0;
                for (int j = i; j < nums.size(); j++) {
                    sum += nums[j];
                    if (sum == 0) {
                        res = {i, j};
                        return res;
                    }
                }
            }
            
            return res;
            
            
        } // end subarraySum
        
        bool wordSegmentation(string s, unordered_set<string> &dict) {
            int n = s.size();
            int minLen = n + 1, maxLen = 0;
            for (auto it = dict.begin(); it != dict.end(); it++) {
                minLen = (*it).size() < minLen ? (*it).size() : minLen;
                maxLen = (*it).size() > maxLen ? (*it).size() : maxLen;
            }
            
            bool f[n+1];
            fill_n(f, n+1, false);
            f[0] = true;
            
            for (int i = 0; i <= n-minLen; i++) {
                if (f[i]) {
                    for (int l = minLen; (l <= maxLen) && (i + l <= n); l++) {
                        string seg = s.substr(i, l);
                        if (dict.find(seg) != dict.end()) {
                            f[i+l] = true;
                        }
                    }
                }
            }
            
            return f[n];
        } // end wordSegmentation
        
        // Longest Increasing Subsequence
        int longestIncreasingSubsequence(vector<int> nums) {
            int n = nums.size();
            if (n == 0) {
                return 0;
            }
            int f[n];
        
            fill_n(f, n, 1);
            
            int longest = 0;
            for (int i = 1; i < n; i++) {
                for (int j = 0; j < i; j++) {
                    if ((nums[i] >= nums[j]) && (f[j] + 1 > f[i])) {
                        f[i] = f[j] + 1;
                        if (f[i] > longest) {
                            longest = f[i];
                        }
                    }
                }
            }
            
            return longest;
        } // end namespace longestIncreasingSubsequence
        
    } // end namespace _DP
    
} // end namespace _lintcode