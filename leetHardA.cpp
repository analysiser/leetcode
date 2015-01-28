//
//  leetHardA.cpp
//  Leetcode
//
//  Created by Xiao Li on 12/26/14.
//  Copyright (c) 2014 Xiao. All rights reserved.
//

#include "leetHardA.h"

namespace _hard {
    
    namespace _033 {
        // 33	Search in Rotated Sorted Array
        int search(int A[], int n, int target) {
            int l = 0;
            int r = n-1;
            while (l <= r) {
                int mid = (l + r)/2;
                if (A[mid] == target)   return mid;
                else if (A[l] <= A[mid]) {
                    if (A[l] <= target && target <= A[mid]) {
                        r = mid-1;
                    }
                    else {
                        l = mid+1;
                    }
                }
                else {
                    if (A[mid] <= target && target <= A[r]) {
                        l = mid+1;
                    }
                    else {
                        r = mid-1;
                    }
                }
            }
            return -1;
        }
    }
    
    namespace _004 {
        
        int partition(int A[], int m, int B[], int n, int left, int right, int pi) {
            int pivot = pi < m ? A[pi] : B[pi-m];
            int *pPivot = pi < m ? A+pi : B+pi-m;
            int *high = right < m ? A+right : B+right-m;
            std::swap(*high, *pPivot);
            int storeIndex = left;
            for (int i = left; i < right; i++) {
                int *v = i < m ? A+i : B+i-m;
                if (*v < pivot) {
                    int *storev = storeIndex < m ? A+storeIndex : B+storeIndex-m;
                    std::swap(*storev, *v);
                    storeIndex+=1;
                }
            }
            int *storev = storeIndex < m ? A+storeIndex : B+storeIndex-m;
            std::swap(*high, *storev);
            return storeIndex;
        }
        
        int select(int A[], int m, int B[], int n, int left, int right, int nth) {
            if (left == right) {
                return left < m ? A[left] : B[left-m];
            }
            int pivotIndex = left;
            pivotIndex = partition(A, m, B, n, left, right, pivotIndex);
            if (pivotIndex == nth)
                return nth < m ? A[nth] : B[nth-m];
            else if (pivotIndex < nth) {
                return select(A, m, B, n, pivotIndex+1, right, nth);
            }
            else {
                return select(A, m, B, n, left, pivotIndex-1, nth);
            }
        }
        
        double findMedianSortedArrays(int A[], int m, int B[], int n) {
            if (m+n == 0)
                return 0;
            bool needTwo = (m+n)%2 == 0;
            if (m == 0) {
                if (needTwo) {
                    return double(B[n/2] + B[n/2-1])/double(2);
                }
                else {
                    return B[n/2];
                }
            }
            if (n == 0) {
                if (needTwo) {
                    return double(A[m/2] + A[m/2-1])/double(2);
                }
                else {
                    return A[m/2];
                }
            }
            
            if (needTwo) {
                int v1 = select(A, m, B, n, 0, m+n-1, (m+n-1)/2);
                int v2 = select(A, m, B, n, 0, m+n-1, (m+n)/2);
                return double(v1+v2)/double(2);
            }
            else {
                return select(A, m, B, n, 0, m+n-1, (m+n)/2);
            }
        }
    }
    
    
    
    namespace _010 {
        
        // 10	Regular Expression Matching, Someone else's solution...
        bool isMatch(const char *s, const char *p) {
            if (!*p)    return (!*s);
            
            if ('*' == *(p + 1)) {
                // x* matches empty string or at least one character: x* -> xx*
                // *s is to ensure s is non-empty
                return (isMatch(s, p + 2) || (*s && (*s == *p || '.' == *p) && isMatch(s + 1, p)) );
            } else {
                if (!*s)    return false;
                return (*s == *p || '.' == *p) ? isMatch(s + 1, p + 1) : false;
            }
        }
    }
    
    namespace _025 {
        // 25   Reverse Nodes in k-Group
        ListNode *reverseKGroup(ListNode *head, int k) {
            
            int size = 0;
            auto tmp = head;
            while (tmp) {
                tmp = tmp->next;
                size++;
            }
            int times = size/k;
            if (size == 0 || times == 0 || k == 1)
                return head;
            
            ListNode *newhead = nullptr;
            for (int i = 0; i < times; i++) {
                int t = 0;
                auto cur = head;
                ListNode *prev = nullptr;
                while(t < k) {
                    auto tmp = cur;
                    cur = cur->next;
                    tmp->next = prev;
                    prev = tmp;
                    t++;
                }
                if (!newhead) {
                    newhead = prev;
                }
                if (i+1<times) {
                    tmp = cur;
                    for(int j = 1; j < k; j++) {
                        tmp=tmp->next;
                    }
                    head->next = tmp;
                    head = cur;
                }
                else {
                    head->next = cur;
                }
            }
            
            return newhead;
        }
    }
    
    
    namespace _030 {
        bool examineSubstring(int index, unordered_map<int, vector<string> > &candidates, unordered_map <string, int> &lut, int totalLen) {
            if (totalLen == 0)  return true;
            auto it = candidates.find(index);
            if (it == candidates.end()) return false;
            else {
                for (int i = 0;i < it->second.size(); i++) {
                    string word = it->second[i];
                    auto wordIt = lut.find(word);
                    if (wordIt->second > 0) {
                        wordIt->second -= 1;
                        bool found = examineSubstring(index + word.size(), candidates, lut, totalLen - word.size());
                        wordIt->second += 1;
                        if (found)  return true;
                    }
                }
                return false;
            }
            
        }
        
        vector<int> findSubstring(string S, vector<string> &L) {
            unordered_map <string, int> lut;
            unordered_set<int> lens;
            int totalLen = 0;
            int minLen = INT_MAX;
            int maxLen = INT_MIN;
            
            for (string word:L) {
                totalLen += word.size();
                minLen = (int)word.size() < minLen ? (int)word.size() : minLen;
                maxLen = (int)word.size() > maxLen ? (int)word.size() : maxLen;
                auto it = lut.find(word);
                if (it == lut.end()) {
                    lut.insert(make_pair(word, 1));
                }
                else {
                    it->second += 1;
                }
                lens.insert((int)word.size());
            }
            
            if (totalLen > S.size()) {
                vector<int> empty;
                return empty;
            }
            
            // make candidates
            unordered_map<int, vector<string> > candidates;
            for (int i = 0; i < S.size(); i++) {
                for (auto itLens = lens.begin(); itLens != lens.end(); itLens ++) {
                    int len = *itLens;
                    if (i+len <= S.size()) {
                        string sub = S.substr(i, len);

                        if (lut.find(sub) != lut.end()) {
                            auto it = candidates.find(i);
                            if (it == candidates.end()) {
                                vector<string> subs = { sub };
                                candidates.insert(make_pair(i, subs));
                            }
                            else {
                                it->second.push_back(sub);
                            }
                        }
                        
                    }
                }
            }
            
            // final examine
            vector<int> sol;
            for (auto it = candidates.begin(); it != candidates.end(); it++) {
                if (examineSubstring(it->first, candidates, lut, totalLen)) {
                    int index = it->first;
                    if (index + totalLen > S.size())
                        continue;
                    sol.push_back(index);
                }
            }
            
            return sol;
        }
    }
    
    
    namespace _032 {
        // 32	Longest Valid Parentheses
        int longestValidParentheses(string s) {
            vector<int> st;
            for (int i = 0; i < s.size(); i++) {
                if (s[i] == '(') {
                    st.push_back(i);
                }
                else {
                    if (!st.empty()) {
                        s[i] = '#';
                        s[st.back()] = '#';
                        st.pop_back();
                    }
                }
            }
            
            int len = 0;
            int cnt = 0;
            for (int i = 0; i < s.size(); i++) {
                if (s[i] == '#') {
                    cnt += 1;
                    len = cnt > len ? cnt : len;
                }
                else {
                    cnt = 0;
                }
            }
            
            return len;
        }
    }
    
    
    namespace _037 {
        // 37	Sudoku Solver
        typedef vector<unordered_set<char> > hashtable;
        
        void insertCell(char c, int i, int j, hashtable &rows, hashtable &cols, hashtable &boxes) {
            rows[i].insert(c);
            cols[j].insert(c);
            int ii = i/3;
            int jj = j/3;
            boxes[3*ii+jj].insert(c);
        }
        
        bool canInsertCell(char c, int i, int j, hashtable &rows, hashtable &cols, hashtable &boxes) {
            int ii = i/3;
            int jj = j/3;
            int k = 3*ii+jj;
            return (rows[i].find(c) == rows[i].end()) &&
            (cols[j].find(c) == cols[j].end()) &&
            (boxes[k].find(c) == boxes[k].end());
        }
        
        void eraseCell(char c, int i, int j, hashtable &rows, hashtable &cols, hashtable &boxes) {
            int ii = i/3;
            int jj = j/3;
            int k = 3*ii+jj;
            
            rows[i].erase(c);
            cols[j].erase(c);
            boxes[k].erase(c);
        }
        
        bool doSolveSudoku(vector<vector<char> > &board,
                           hashtable &rows,
                           hashtable &cols,
                           hashtable &boxes,
                           vector<pair<int, int> > &cells,
                           int index) {
            if (index == cells.size()) {
                return true;
            }
            
            int i = cells[index].first;
            int j = cells[index].second;
            
            for (char c = '1'; c <= '9'; c++) {
                if (canInsertCell(c, i, j, rows, cols, boxes)) {
                    board[i][j] = c;
                    insertCell(c, i, j, rows, cols, boxes);
                    if (doSolveSudoku(board, rows, cols, boxes, cells, index+1) )
                        return true;
                    eraseCell(c, i, j, rows, cols, boxes);
                    board[i][j] = '.';
                }
            }
            return false;
        }
        
        void solveSudoku(vector<vector<char> > &board) {
            unordered_set<char> empty;
            hashtable rows(9, empty);
            hashtable cols(9, empty);
            hashtable boxes(9, empty);
            vector<pair<int, int> > cells;
            for (int i = 0; i < board.size(); i++) {
                for (int j = 0; j < board[i].size(); j++) {
                    char v = board[i][j];
                    if (v != '.') {
                        insertCell(v, i, j, rows, cols, boxes);
                    }
                    else {
                        cells.push_back(make_pair(i, j));
                    }
                }
            }
            
            doSolveSudoku(board, rows, cols, boxes, cells, 0);
        }
    }
    
    
    namespace _041 {
        // 41	First Missing Positive
        int firstMissingPositive(int A[], int n) {
            for (int i = 0; i < n; i++) {
                int v = A[i];
                while ((v != (i+1)) && v > 0 && v <= n && (A[i] != A[v-1])) {
                    swap(A[i], A[v-1]);
                    v = A[i];
                }
            }
            
            for (int i = 0; i < n; i++) {
                if (A[i] != i+1) {
                    return i+1;
                }
            }
            return (n+1);
        }
    }
    
    
    namespace _042 {
        
        int trap(int A[], int n) {
            int l = 0, r = n - 1;
            int res = 0;
            while (l < r) {
                while (A[l] <= 0)   l++;
                while (A[r] <= 0)   r--;
                if (l < r) {
                    int min = A[l] < A[r] ? A[l] : A[r];
                    int total = (r+1-l)*min;
                    
                    for (int i = l; i <= r; i++) {
                        int deduct = A[i] < min ? A[i] : min;
                        total -= deduct;
                        A[i] -= deduct;
                    }
                    res += total;
                }
            }
            
            return res;
        }
    }
    
    
    namespace _044 {
        
        bool isMatch(const char *s, const char *p) {

            const char *star = NULL;
            const char *ss = s;
            while(*s) {
                if (*s == *p || *p == '?') {
                    s++;
                    p++;
                    continue;
                }
                
                if (*p == '*') {
                    star = p;
                    ss = s;
                    p++;
                    continue;
                }
                
                if (star) {
                    p = star+1;
                    s = ++ss;
                    continue;
                }
                
                return false;
            }
            
            while (*p=='*'){p++;}
            return !*p;
        }
        
        
    }
    
    namespace _045 {
        
        int jump(int A[], int n) {

            if (n<2)    return 0;
            
            int *steps = new int[n];
            fill_n(steps, n, INT_MAX);
            steps[0] = 0;
            
            int right = 0;
            for (int i = 0; i < n; i++) {
                int m = i+A[i];
                if (m >= n-1)
                    return steps[i]+1;
                else {
                    if (m > right) {
                        fill_n(steps + right + 1, m-right, steps[i]+1);
                        right = m;
                    }
                }
            }
            
            return steps[n-1];
        }
    }
    
    namespace _047 {
        void dfs(vector<vector<int> > &res, vector<int> &sol, unordered_map<int, int> &lut, int total) {
            if (sol.size() == total) {
                res.push_back(sol);
            }
            else {
                for (auto it = lut.begin(); it != lut.end(); it++) {
                    if (it->second > 0) {
                        it->second -= 1;
                        sol.push_back(it->first);
                        dfs(res, sol, lut, total);
                        sol.pop_back();
                        it->second += 1;
                    }
                }
            }
        }
        
        vector<vector<int> > permuteUnique(vector<int> &num) {
            int total = num.size();
            unordered_map<int, int> lut;
            for (int n : num) {
                auto it = lut.find(n);
                if (it == lut.end()) {
                    lut.insert(make_pair(n, 1));
                }
                else {
                    it->second += 1;
                }
            }
            
            vector<int> sol;
            vector<vector<int> > res;
            
            dfs(res, sol, lut, total);
            
            return res;
        }
    }
    
}

