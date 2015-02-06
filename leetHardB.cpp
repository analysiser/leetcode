//
//  leetHardB.cpp
//  Leetcode
//
//  Created by Xiao Li on 2/6/15.
//  Copyright (c) 2015 Xiao. All rights reserved.
//

#include "leetHardB.h"

namespace _hard {
    
    namespace _076 {
        string minWindow(string S, string T) {
            if ((T.size() == 0) || (T.size() > S.size())) {
                return "";
            }
            
            int count = (int)T.size();
            int needs[128] = { 0 };
            bool chset[128] = { false };
            
            for (int i = 0; i < T.size(); i++) {
                needs[T[i]]++;
                chset[T[i]] = true;
            }
            
            int index = -1;
            int minLen = INT_MAX;
            int i = -1;
            int j = 0;
            while ((i < (int)S.size()) && (j < S.size() - T.size() + 1)) {
                if (count) {
                    i++;
                    needs[S[i]] -= 1;
                    if ((needs[S[i]] >= 0) && (chset[S[i]])) {
                        count--;
                    }
                }
                else {
                    if (minLen > i - j + 1) {
                        minLen = i - j + 1;
                        index = j;
                    }
                    needs[S[j]] += 1;
                    if ((needs[S[j]] > 0) && (chset[S[j]])) {
                        count++;
                    }
                    j++;
                }
            }
            
            if (index == -1) {
                return "";
            }
            else {
                return S.substr(index, minLen);
            }
        }
    }
    
    namespace _084 {
        int largestRectangleArea(vector<int> &height) {
            
            int maxArea = 0;
            vector<int> indices;
            height.push_back(0);
            
            for (int i = 0; i < height.size(); i++) {
                while (indices.size() && (height[i] < height[indices.back()])) {
                    int h = height[indices.back()];
                    indices.pop_back();
                    int idx = indices.size() > 0 ? indices.back() : -1;
                    int area = h * (i - idx - 1);
                    maxArea = area > maxArea ? area : maxArea;
                }
                indices.push_back(i);
            }
            
            return maxArea;
        }
    }
    
    namespace _085 {
        int maximalRectangle(vector<vector<char> > &matrix) {
            
            if (matrix.size() == 0) {
                return 0;
            }
            if (matrix[0].size() == 0) {
                return 0;
            }
            
            int m = matrix.size();
            int n = matrix[0].size();
            
            int left[n];
            int right[n];
            int height[n];
            fill_n(left,n,0); fill_n(right,n,n); fill_n(height,n,0);
            int l = 0, r = n, maxA = 0;
            
            for (int i = 0; i < m; i++) {
                l = 0;
                r = n;
                for (int j = 0; j < n; j++) {
                    if (matrix[i][j] == '1') {
                        height[j]++;
                        left[j] = max(left[j], l);
                    }
                    else {
                        height[j] = 0;
                        left[j] = 0;
                        l = j+1;
                    }
                }
                
                for (int j = n-1; j >= 0; j--) {
                    if (matrix[i][j] == '1') {
                        right[j] = min(right[j], r);
                    }
                    else {
                        right[j] = n;
                        r = j;
                    }
                }
                
                for (int j = 0; j < n; j++) {
                    maxA = max(maxA, (right[j] - left[j]) * height[j]);
                }
            }
            
            return maxA;
        }
    }
    
    namespace _087 {
        bool isScramble(string s1, string s2) {
            if (s1.size() != s2.size()) {
                return false;
            }
            
            int len = (int)s1.size();
            bool f[len][len][len+1];
            memset(f, false, len * len * (len + 1) * sizeof(bool));
            f[0][0][0] = true;
            
            for (int k = 1; k <= len; k++) {
                for (int i = 0; i <= len-k; i++) {
                    for (int j = 0; j <= len-k; j++) {
                        if (k == 1) {
                            f[i][j][k] = (s1[i] == s2[j]);
                        }
                        else {
                            for (int l = 1; l < k; l++) {
                                if ((f[i][j][l] && f[i+l][j+l][k-l]) ||
                                    (f[i][j+k-l][l] && f[i+l][j][k-l])) {
                                    f[i][j][k] = true;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            
            return f[0][0][len];
        }
    }

    
}
