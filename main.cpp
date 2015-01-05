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
//    cout<<(0^0)<<endl;
//    cout<<divide(-2147483648, -1)<<endl;
//    cout<<multiply("1002323111132", "2000000")<<endl;
    vector<int> num = {1, 2, 3};
    auto permutations = permute(num);
    for (vector<int> res : permutations) {

        for (int i = 0; i < res.size(); i++) {
            cout<<res[i]<<",";
        }
        cout<<endl;
    }
    
    
    return 0;
}
