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
    
    namespace _023 {
        
        ListNode *merge2(ListNode *l1, ListNode *l2) {
            if (!l1) {
                return l2;
            }
            if (!l2) {
                return l1;
            }
            
            ListNode *head = NULL;
            ListNode *cur = NULL;
            
            while (l1 && l2) {
                ListNode *tmp = NULL;
                if (l1->val <= l2->val) {
                    tmp = l1;
                    l1 = l1->next;
                    tmp->next = NULL;
                }
                else {
                    tmp = l2;
                    l2 = l2->next;
                    tmp->next = NULL;
                }
                if (!head) {
                    head = tmp;
                    cur = head;
                }
                else {
                    cur->next = tmp;
                    cur = cur->next;
                }
            }
            if (l1) {
                cur->next = l1;
            }
            if (l2) {
                cur->next = l2;
            }
            
            return head;
        }
        
        ListNode *mergeKLists(vector<ListNode *> &lists) {
            if (lists.size() == 0) {
                return nullptr;
            }
            if (lists.size() == 1) {
                return lists[0];
            }
            
            vector<ListNode *> next = lists;
            decltype(next) cur;
            
            while (next.size() > 1) {
                if (next.size()%2) {
                    next.push_back(NULL);
                }
                for (int i = 0; i < next.size()-1; i +=2) {
                    ListNode *merged = merge2(next[i], next[i+1]);
                    if (merged) {
                        cur.push_back(merged);
                    }
                }
                next = cur;
                cur.clear();
            }
            
            return next[0];
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
    
    
    namespace _051 {
        const int steps[4][2] = { {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };
        
        void insertQueen(vector<string> &sol, int r, int c, int n) {
            for (int j = 0; j < n; j++) {
                sol[r][j] = '*';
            }
            for (int i = 0; i < n; i++) {
                sol[i][c] = '*';
            }
            for (int i = 0; i < 4; i++) {
                int p = r+steps[i][0];
                int q = c+steps[i][1];
                while(p >= 0 && q >= 0 && p < n && q < n) {
                    sol[p][q] = '*';
                    p += steps[i][0];
                    q += steps[i][1];
                }
            }
            sol[r][c] = 'Q';
        }
        
        void nqueenDFS(vector<vector<string> > &res, vector<string> sol, int r, int c, int n, int k) {
            
            insertQueen(sol, r, c, n);
            k -= 1;
            if ( k == 0) {
                for (string &s : sol) {
                    for (char &c : s) {
                        if (c == '*')
                            c = '.';
                    }
                }
                res.push_back(sol);
                return;
            }
            else {
                for (int i = 0; i < n; i++) {
                    if (sol[r+1][i] == '.') {
                        nqueenDFS(res, sol, r+1, i, n, k);
                    }
                }
            }
        }
        
        vector<vector<string> > solveNQueens(int n) {
            string line(n, '.');
            vector<string> board(n, line);
            vector<vector<string> > res;
            
            for (int i = 0; i < n; i++) {
                nqueenDFS(res, board, 0, i, n, n);
            }
            
            return res;
        }
    }
    
    namespace _052 {
        const int steps[4][2] = {{-1,-1}, {-1, 1}, {1, -1}, {1, 1}};
        
        void insertQueen(vector<vector<int> > &board, int r, int c, int n) {
            for (int i = 0; i < n; i++) {
                board[i][c] = 0;
            }
            for (int i = 0; i < 4; i++) {
                int p = r;
                int q = c;
                while (p >= 0 && q >= 0 && q < n && p < n) {
                    board[p][q] = 0;
                    p += steps[i][0];
                    q += steps[i][1];
                }
            }
        }
        
        void nqueenDFS(vector<vector<int> > board, int r, int c, int n, int k, int &total) {
            insertQueen(board, r, c, n);
            k -= 1;
            if (k == 0) {
                total += 1;
                return;
            }
            
            for (int j = 0; j < n; j++) {
                if (board[r+1][j] == 1) {
                    nqueenDFS(board, r+1, j, n, k, total);
                }
            }
        }
        
        int totalNQueens(int n) {
            if (n == 0) return 0;
            if (n == 1) return 1;
            
            vector<int> line(n, 1);
            vector<vector<int> > board(n, line);
            int total = 0;
            for (int j = 0; j < n; j++) {
                nqueenDFS(board, 0, j, n, n, total);
            }
            return total;
        }
    }
    
    
    namespace _056 {
        
        static bool comparator(const Interval &a, const Interval &b) {
            return a.start < b.start;
        }
        
        vector<Interval> merge(vector<Interval> &intervals) {
            if (intervals.size() < 2)   return intervals;
            
            std::sort(intervals.begin(), intervals.end(), comparator);
            vector<Interval> res;
            Interval cur = intervals[0];
            for (int i = 1; i < intervals.size() - 1; i++) {
                if (intervals[i].start <= cur.end) {
                    cur.end = intervals[i].end > cur.end ? intervals[i].end : cur.end;
                }
                else {
                    res.push_back(cur);
                    cur = intervals[i];
                }
            }
            
            Interval last = intervals.back();
            if (last.start <= cur.end) {
                cur.end = last.end > cur.end ? last.end : cur.end;
                res.push_back(cur);
            }
            else {
                res.push_back(cur);
                res.push_back(last);
            }
            
            return res;
        }
    }
    
    namespace _057 {
        vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
            int l = newInterval.start;
            int r = newInterval.end;
            vector<Interval> res;
            bool inserted = false;
            for (int i = 0; i < intervals.size(); i++) {
                if (intervals[i].end < l) {
                    res.push_back(intervals[i]);
                    continue;
                }
                else if (intervals[i].start > r) {
                    if (!inserted) {
                        newInterval.start = l;
                        newInterval.end = r;
                        res.push_back(newInterval);
                        inserted = true;
                    }
                    res.push_back(intervals[i]);
                }
                else {
                    l = min(intervals[i].start, l);
                    r = max(intervals[i].end, r);
                }
            }
            
            if (!inserted) {
                newInterval.start = l;
                newInterval.end = r;
                res.push_back(newInterval);
            }
            
            return res;
        }
    }
    
    
    namespace _068 {
        vector<string> fullJustify(vector<string> &words, int L) {
            vector<string> res;
            if (words.size() == 0) {
                string sp(L, ' ');
                res.push_back(sp);
                return res;
            }
            
            for (int i = 0; i < words.size();) {
                int size = 0;
                int last = -1;
                for (int j = i; j < words.size(); j++) {
                    size += words[j].size();
                    // j - i: how many single spaces needed
                    if (size + j - i > L) {
                        last = j-1 > i ? j-1 : i;
                        size -= words[j].size();
                        break;
                    }
                }
                if (last != -1) {
                    int count = last-i+1;
                    int spaces = L - size;
                    if (spaces >= 0) {
                        int spCount = count > 2 ? spaces/(count-1) : spaces;
                        int spSurplus = count > 2 ? spaces%(count - 1) : 0;
                        string line = "";
                        for (int j = i; j <= last; j++) {
                            string tmp = words[j];
                            string sp(spCount + (spSurplus > 0 ? 1 : 0), ' ');
                            if (i != last && j == last) {
                                sp = "";
                            }
                            line += tmp + sp;
                            spSurplus -= 1;
                        }
                        res.push_back(line);
                    }
                    else {
                        // the word cannot fit in a single line
                        string word = words[i];
                        for (int k = 0; k < word.size(); k += L) {
                            int len = std::min(L, int(word.size()-k));
                            string tmp = word.substr(k, len);
                            if (len < L) {
                                // this is hacky...
                                string sp(L-len, ' ');
                                tmp += sp;
                            }
                            res.push_back(tmp);
                        }
                    }
                    
                    i = last + 1;
                    
                }
                else {
                    // end of words
                    last = words.size()-1;
                    string line = "";
                    for (int j = i; j <= last; j++) {
                        line += words[j] + " ";
                    }
                    if (line.size() > L) {
                        line = line.substr(0, line.size()-1);
                    }
                    else if (line.size() < L) {
                        string sp(L-line.size(), ' ');
                        line += sp;
                    }
                    
                    res.push_back(line);
                    break;
                }
            }
            
            return res;
        }
    }
    
    
    namespace _072 {
        namespace _sol1 {
            int minDistance(string word1, string word2) {
                
                if (word1 == word2) {
                    return 0;
                }
                if ( (word1.size() == 0) || (word2.size() == 0) ) {
                    return (int)word1.size() ^ (int)word2.size();
                }
                if (word1.size() > word2.size()) {
                    swap(word1, word2);
                }
                
                int steps = (int)word2.size();
                int len = (int)word1.size();
                for (; len >= 1; len--) {
                    unordered_map<string, vector<int>> mapw1, mapw2;
                    for (int i = 0; i < word1.size() - len + 1; i++) {
                        string sub = word1.substr(i, len);
                        auto it= mapw1.find(sub);
                        if (it == mapw1.end()) {
                            vector<int> indices = {i};
                            mapw1.insert(make_pair(sub, indices));
                        }
                        else {
                            it->second.push_back(i);
                        }
                    }
                    for (int i = 0; i < word2.size() - len + 1; i++) {
                        string sub = word2.substr(i, len);
                        auto it= mapw2.find(sub);
                        if (it == mapw2.end()) {
                            vector<int> indices = {i};
                            mapw2.insert(make_pair(sub, indices));
                        }
                        else {
                            it->second.push_back(i);
                        }
                    }
                    
                    for (auto it = mapw1.begin(); it != mapw1.end(); it++) {
                        string sub = it->first;
                        auto it2 = mapw2.find(sub);
                        if (it2 != mapw2.end()) {
                            
                            for (int index1 : it->second) {
                                for (int index2 : it2->second) {
                                    
                                    int step = 0;
                                    step += minDistance(word1.substr(0, index1), word2.substr(0, index2));
                                    int m = index1 + len;
                                    int n = index2 + len;
                                    step += minDistance(word1.substr(m, word1.size()-m), word2.substr(n, word2.size()-n));
                                    if (step < steps) {
                                        steps = step;
                                    }
                                }
                            }
                        }
                    } // end for auto it
                    
                    if (steps < word2.size()) {
                        return steps;
                    }
                }
                
                return (int)word2.size();
            }
        }
        
        namespace _sol2 {
            int minDistance(string word1, string word2) {
                int m = int(word1.size());
                int n = int(word2.size());
                if ((m == 0) || (n == 0)) {
                    return m ^ n;
                }
                
                int A[m+1][n+1];
                for (int i = 0; i <= m; i++) {
                    A[i][0] = i;
                }
                for (int j = 0; j <= n; j++) {
                    A[0][j] = j;
                }
                
                for (int i = 1; i <= m; i++) {
                    char c = word1[i-1];
                    for (int j = 1; j <= n; j++) {
                        int cost = 1;
                        if (c == word2[j-1]) {
                            cost = 0;
                        }
                        A[i][j] = std::min(A[i-1][j] + 1, A[i][j-1] + 1);
                        A[i][j] = std::min(A[i][j], A[i-1][j-1]+cost);
                    }
                }
                
                return A[m][n];
             }
        }
        
            }
    namespace _154 {
        // 154	Find Minimum in Rotated Sorted Array II
        int findMin(vector<int> &num) {
            int min = INT_MAX;
            for (int i = 0; i < num.size(); i++) {
                min = num[i] < min ? num[i] : min;
            }
            return min;
        }
        
    }
    
    namespace _132 {
        bool isPalindrome(string s, int l, int r) {
            while (l < r) {
                if (s[l] != s[r]) {
                    return false;
                }
                l++;
                r--;
            }
            return true;
        }
        
        pair<int, int> longestPalindrome(string s) {
            if (s.size() == 0) {
                return make_pair(0, 0);
            }
            if (s.size() == 1) {
                return make_pair(0, 1);
            }
            
            int i = 0;
            int l = 0;
            for (int j = 0; j < s.size(); j++) {
                if ((j-l-1) >= 0 && isPalindrome(s, j-l-1, j)) {
                    i = j-l-1;
                    l += 2;
                }
                else if (isPalindrome(s, j-l, j)) {
                    i = j-l;
                    l += 1;
                }
            }
            return make_pair(i, i+l-1);
        }
        
        int minCut(string s) {
            if (s.size() < 2) {
                return 0;
            }
            pair<int, int> info = longestPalindrome(s);
            int count = 2;
            // left
            if (info.first == 0) {
                count -= 1;
            }
            else {
                count += minCut(s.substr(0, info.first));
            }
            //right
            if (info.second == s.size()-1) {
                count -= 1;
            }
            else {
                count += minCut(s.substr(info.second+1, s.size()-info.second-1));
            }
            return count;
            
        }
    }

}

