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
        }
        
    }
    
} // end namespace _lintcode