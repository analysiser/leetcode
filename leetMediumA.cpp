//
//  leetMediumA.cpp
//  Leetcode
//
//  Created by Xiao Li on 12/26/14.
//  Copyright (c) 2014 Xiao. All rights reserved.
//

#include "leetMediumA.h"


struct pairhash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first * 1000 + v.second;
    }
};

string longestPalindrome(string s) {
    
    if (s.length() == 0)    return "";
    if (s.length() < 3)    return s;
    int left = -1;
    int maxLen = -1;
    
    unordered_set<pair<int, int>, pairhash > next;
    
    for (int i = 0; i < s.length() - 1; i++)
        if (s[i] == s[i+1])
            next.insert(make_pair(i, i+1));
    
    for (int i = 0;i < s.length() - 2; i++)
        if (s[i] == s[i+2])
            next.insert(make_pair(i, i+2));
    
    for (pair<int, int> p : next)
    {
        int i = p.first;
        int j = p.second;
        int pLen = 2 * std::min(i, (int)(s.length() - j - 1)) + j - i + 1;
        if (pLen <= maxLen)
            continue;

        while (i >= 0 && j < s.length() && s[i] == s[j]) {
            i--;
            j++;
        }
        i += 1;
        j -= 1;
        int len = j-i+1;
        if (len > maxLen)
        {
            maxLen = len;
            left = i;
        }
    }

    
    return s.substr(left, maxLen);
}

bool isPanlindrome(string &s, int l, int r)
{
    while (l < r) {
        if (s[l] != s[r])
            return false;
        l++;
        r--;
    }
    return true;
}

/*
 suppose
 
 string(i,l) is a substring of s where i is the start index and l is the length
 
 S(n) is the longest palindrome for substring of s with indice from 0 to n
 if S(n-1) = string(i,l)
 
 then S(n) =
 
 string(n-l, l+1) if string(n-l, l+1) is palindrome
 string(n-l-1, l+2) if string(n-l-1, l+2) is palindrome
 S(n-1) otherwise
 
 */
string longestPalindrome2(string s)
{
    int i = 0;
    int l = 0;
    int n = s.length();
    for (int j = 0; j < n; j++) {
        if (j-l-1 >= 0 && isPanlindrome(s, j-l-1, j))
        {
            i = j-l-1;
            l = l+2;
        }
        else if (isPanlindrome(s, j-l, j))
        {
            i = j-l;
            l = l+1;
        }
        
    }
    return s.substr(i, l);
}

vector<vector<int> > fourSum(vector<int> &num, int target) {
    vector<vector<int> > ret;
    size_t n = num.size();
    if (n < 4) return ret;
    
    sort(num.begin(), num.end());
    if (target > num[n-1] + num[n-2] + num[n-3] + num[n-4]) return ret;
    if (target < num[0] + num[1] + num[2] + num[3]) return ret;
    
    // get 2 sum maps, and count LUT for further checking
    map<int, vector<pair<int, int> > > map1;
    map<int, int> countLUT;
    for (int i = 0; i < n; i++) {
        auto countIt = countLUT.find(num[i]);
        if (countIt == countLUT.end())
            countLUT.insert(make_pair(num[i], 1));
        else
            countIt->second += 1;
        
        for (int j = i + 1; j < n; j++) {
            int sum = num[i] + num[j];
            auto it = map1.find(sum);
            if (it == map1.end())
            {
                vector<pair<int, int> > apair;
                apair.push_back(make_pair(num[i], num[j]));
                map1.insert(make_pair(sum, apair));
            }
            else
            {
                it->second.push_back(make_pair(num[i], num[j]));
            }
        }
    }

    // get pairs that can combine the values
    vector<pair<int, int> > toCombine;
    for (auto it = map1.begin(); it != map1.end(); it++) {
        int x = it->first;
        int y = target - x;
        if (y < x)  break;
        auto found = map1.find(y);
        if (found != map1.end()) {
            toCombine.push_back(make_pair(x, y));
        }
    }
    
    // generate unique lists of results using string as keys
    unordered_set<string> uniqueResults;
    
    for (pair<int, int> &p : toCombine) {
        int i = p.first;
        int j = p.second;
        if (i == j)
        {
            auto it = map1.find(i);
            auto pairs = it->second;
            for (int p = 0; p < pairs.size(); p++) {
                for (int q = p + 1; q < pairs.size(); q++) {
                    int res[4];
                    res[0] = pairs[p].first;
                    res[1] = pairs[p].second;
                    res[2] = pairs[q].first;
                    res[3] = pairs[q].second;
                    
                    // check if exceeds max repeated numbers limits
                    map<int, int> check;
                    for (int idx = 0; idx < 4; idx++) {
                        auto checkIt = check.find(res[idx]);
                        if (checkIt == check.end())
                            check.insert(make_pair(res[idx], 1));
                        else
                            checkIt->second += 1;
                    }
                    
                    bool pass = true;
                    for (auto checkIt = check.begin(); checkIt != check.end(); checkIt++) {
                        int number = checkIt->first;
                        if (countLUT.find(number)->second < checkIt->second) {
                            pass = false;
                            break;
                        }
                    }
                    
                    if (pass)
                    {
                        vector<int> sol = {res[0], res[1], res[2], res[3]};
                        sort(sol.begin(), sol.end());
                        // check uniqueness
                        string key = to_string(sol[0]) + ',' + to_string(sol[1]) + ',' + to_string(sol[2]) + ',' + to_string(sol[3]);
                        if (uniqueResults.find(key) == uniqueResults.end())
                        {
                            ret.push_back(sol);
                            uniqueResults.insert(key);
                        }
                    }
                }
            }
            
        }
        else
        {
            auto iti = map1.find(i);
            auto itj = map1.find(j);
            
            auto pairs1 = iti->second;
            auto pairs2 = itj->second;
            
            for (int p = 0; p < pairs1.size(); p++) {
                for (int q = 0; q < pairs2.size(); q++) {
                    int res[4];
                    res[0] = pairs1[p].first;
                    res[1] = pairs1[p].second;
                    res[2] = pairs2[q].first;
                    res[3] = pairs2[q].second;
                    
                    // check if exceeds max repeated numbers limits
                    map<int, int> check;
                    for (int idx = 0; idx < 4; idx++) {
                        auto checkIt = check.find(res[idx]);
                        if (checkIt == check.end())
                            check.insert(make_pair(res[idx], 1));
                        else
                            checkIt->second += 1;
                    }
                    
                    bool pass = true;
                    for (auto checkIt = check.begin(); checkIt != check.end(); checkIt++) {
                        int number = checkIt->first;
                        if (countLUT.find(number)->second < checkIt->second) {
                            pass = false;
                            break;
                        }
                    }
                    
                    if (pass)
                    {
                        vector<int> sol = {res[0], res[1], res[2], res[3]};
                        sort(sol.begin(), sol.end());
                        // check uniqueness
                        string key = to_string(sol[0]) + ',' + to_string(sol[1]) + ',' + to_string(sol[2]) + ',' + to_string(sol[3]);
                        if (uniqueResults.find(key) == uniqueResults.end())
                        {
                            ret.push_back(sol);
                            uniqueResults.insert(key);
                        }
                    }
                }
            }
            
        }
            
    }

    return ret;
}


string simplifyPath(string path)
{
    vector<string> dirs;
    string dir = "";
    string wrap = "/";
    wrap += path;
    wrap += '/';
    path = wrap;
    for (int i = 0; i < path.length(); i++)
    {
        char cur = path[i];
        if (cur == '/')
        {
            if (dir != "")
            {
                if (dir == ".") {
                    
                }
                else if (dir == "..")
                {
                    if (!dirs.empty())
                    {
                        dirs.pop_back();
                    }
                }
                else if (dir == "~")
                {
                    dirs.clear();
                }
                else
                {
                    dirs.push_back(dir);
                }
                dir = "";
            }
        }
        else
        {
            dir += cur;
        }
    }
    
    string ret = "/";
    for (auto it = dirs.begin(); it != dirs.end(); it++)
    {
        ret += *it;
        ret += '/';
    }
    ret = ret.substr(0, ret.length() - 1);
    if (ret == "")
        return "/";
    else
        return ret;
}


void generateParenthesisDFS(int l, int r, string s, vector<string> &res)
{
    if (l == 0)
    {
        for (int i = 0; i < r; i++)
            s += ')';
        res.push_back(s);
    }
    else
    {
        if (l == r)
        {
            generateParenthesisDFS(l-1, r, s + '(', res);
        }
        else if (l < r)
        {
            generateParenthesisDFS(l-1, r, s +'(', res);
            generateParenthesisDFS(l, r-1, s +')', res);
        }
    }
}

vector<string> generateParenthesis(int n) {
    vector<string> ret;
    if (n == 0) return ret;
    
    generateParenthesisDFS(n, n, "", ret);
    return ret;
}


int divide(int dividend, int divisor) {
    int64_t m = dividend;
    int64_t n = divisor;
    int sign = (m < 0 ^ n < 0) == 0 ? 1 : -1;
    if (n == 0)
        return sign == -1 ? INT_MIN : INT_MAX;
    if (m == 0)
        return 0;
    m = abs(m);
    n = abs(n);
    if (n > m)  return 0;
    
    int64_t q = 0;
    int64_t t = 0;
    for (int i = 31; i >=0; i--)
    {
        int64_t k = n << i;
        if (t + k <= m)
        {
            t += k;
            q |= int64_t(1) << i;
        }
    }
    
    q = (sign == -1) ? -q : q;
    return (q > INT_MAX ? INT_MAX : q < INT_MIN ? INT_MIN : q);
}

void nextPermutation(vector<int> &num) {
    int n = (int)num.size();
    if (n < 2)  return;
    int l = n-2;
    for (; l>=0; l--) {
        if (num[l] < num[l+1])  break;
    }
    if (l >= 0)
    {
        int r = n - 1;
        for (; r > l; r--)
        {
            if (num[l] < num[r]) {
                swap(num[l], num[r]);
                break;
            }
        }
    }
    reverse(num.begin() + l + 1, num.end());
}

void search(int A[], int l, int r, int &i, int &j, int target)
{
    if (l <= r)
    {
        int mid = (l + r)/2;
        int v = A[mid];
        if (v < target)
        {
            search(A, mid + 1, r, i, j, target);
        }
        else if (v > target)
        {
            search(A, l, mid - 1, i, j, target);
        }
        else
        {
            if (i == -1 || mid < i)
                i = mid;
            if (j == -1 || mid > j)
                j = mid;
            search(A, mid + 1, r, i, j, target);
            search(A, l, mid - 1, i, j, target);
        }
    }
}

vector<int> searchRange(int A[], int n, int target) {
    int i = -1, j = -1;
    search(A, 0, n-1, i, j, target);
    vector<int> res = {i, j};
    return res;
}

void combinationSumSearch(vector<int> &c, deque<int> &res, vector<vector<int> > &sol, int target, int r)
{
    for (int i = r; i >= 0; i--)
    {
        int v = c[i];
        if (v == target)
        {
            res.push_front(v);
            vector<int> asol = vector<int>(res.begin(), res.end());
            sol.push_back(asol);
            res.pop_front();
        }
        else if (v < target)
        {
            res.push_front(v);
            combinationSumSearch(c, res, sol, target - v, i);
            res.pop_front();
        }
    }
}

vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
    set<int> canset;
    for (int c : candidates)
    {
        if (canset.find(c) == canset.end())
            canset.insert(c);
    }
    vector<int> canvec = vector<int>(canset.begin(), canset.end());
    vector<vector<int> > sol;
    deque<int> res;
    combinationSumSearch(canvec, res, sol, target, canvec.size()-1);
    return sol;
}

string multiply(string num1, string num2) {
    string a, b;
    if(num1.length() >= num2.length()) {
        a = num1;
        b = num2;
    }
    else {
        a = num2;
        b = num1;
    }
    
    if (a.length() == 0)    return b;
    if (b.length() == 0)    return a;
    
    vector<string> sums;
    int fraction_cnt = 0;
    for (int i = a.length(); i >= 0; i--)
        if (a[i] == '.')
        {
            fraction_cnt += a.length() - i - 1;
            break;
        }
    for (int i = b.length(); i >= 0; i--)
        if(b[i] == '.')
        {
            fraction_cnt += b.length() - i - 1;
            break;
        }
    
    for (int i = b.length() - 1; i >= 0; i--)
    {
        int carry = 0;
        string step = "";
        for (int j = a.length() - 1; j >= 0; j--)
        {
            if (b[i] == '.')    i--;
            if (a[j] == '.')    j--;
            int x = b[i]-'0';
            int y = a[j]-'0';
            int val = (x * y + carry);
            int res = val%10;
            carry = val/10;
            step += res + '0';
        }
        if (carry > 0)
            step += carry + '0';
        sums.push_back(step);
    }
    
    string sol=sums[0];
    for (int i = 1; i < sums.size(); i++)
    {
        string s = sums[i];
        int carry = 0;
        string temp = sol.substr(0, i);
        for(int j = 0; j < s.length(); j++)
        {
            int x = 0;
            if (j + i < sol.length())
                x = sol[j + i] - '0';
            int y = s[j] - '0';
            int val = x + y + carry;
            int res = val % 10;
            carry = val / 10;
            temp += res + '0';
        }
        
        if (carry > 0)
            temp += carry + '0';
        sol = temp;
    }
    
    if (fraction_cnt > 0)
    {
        string temp = sol.substr(0, fraction_cnt);
        temp += '.';
        temp += sol.substr(fraction_cnt, sol.length() - fraction_cnt);
        sol = temp;
    }
    int zero_cnt = 0;
    for (int i = sol.length() - 1; i > 0; i--) {
        if (sol[i] == '0') {
            zero_cnt++;
        }
        else
            break;
    }
    
    sol = sol.substr(0, sol.length() - zero_cnt);
    
    return string(sol.rbegin(), sol.rend());
}


string multiply2(string num1, string num2) {
    if (num1 == "0" || num2 == "0")
        return "0";
    
    string sol = "";
    int carry = 0;
    for (int i = 1; i < num1.size() + num2.size(); i++)
    {
        int sum = carry;
        for (int j = 1; j <= num1.size(); j++)
        {
            int k = i-j+1;
            if (k >= 1 && k <= num2.size())
            {
                sum += (num1[num1.size() - j] - '0') * (num2[num2.size() - k] - '0');
            }
        }
        sol.insert(sol.begin(), sum%10 + '0');
        carry = sum/10;
    }
    if (carry > 0)
        sol.insert(sol.begin(), carry + '0');
    
    return sol;
    
}


// 46 Permutations
void doPermute(map<int, int> &lut, vector<int> &keys, size_t n, vector<int> &res, vector<vector<int> > &sol)
{
    if (res.size() == n) {
        sol.push_back(res);
        return;
    }
    for (int i = 0; i < keys.size(); i++)
    {
        int v = keys[i];
        auto it = lut.find(v);
        if (it->second > 0)
        {
            it->second -= 1;
            res.push_back(v);
            doPermute(lut, keys, n, res, sol);
            res.pop_back();
            it->second += 1;
        }
    }
}

vector<vector<int> > permute(vector<int> &num) {
    map<int, int> lut;
    for (int n:num)
    {
        auto it = lut.find(n);
        if (it == lut.end())
            lut.insert(make_pair(n,1));
        else
            it->second++;
    }
    
    vector<int> keys;
    for(auto it = lut.begin(); it != lut.end(); it++)
        keys.push_back(it->first);
    vector<int> res;
    vector<vector<int> > sol;
    
    doPermute(lut, keys, num.size(), res, sol);
    
    return sol;
}

void rotate(vector<vector<int> > &matrix) {
    size_t w = matrix[0].size();
    size_t h = matrix.size();
    auto res = matrix;
    for (size_t i = 0; i < h; i++) {
        for (size_t j = 0; j < w; j++) {
            size_t x = w-1-j;
            size_t y = i;
            res[i][j] = matrix[x][y];
        }
    }
    matrix = res;
}
void rotate2(vector<vector<int> > &matrix) {
    size_t n = matrix[0].size();
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i; j < n - i - 1; j++) {
            int tmp = matrix[i][j];
            matrix[i][j] = matrix[n-1-j][i];
            matrix[n-1-j][i] = matrix[n-1-i][n-1-j];
            matrix[n-1-i][n-1-j] = matrix[j][n-1-i];
            matrix[j][n-1-i] = tmp;
        }
    }
}

// 49 Anagrams
vector<string> anagrams(vector<string> &strs) {
    unordered_map<string, vector<int> > lut;
    for (int i = 0; i < strs.size(); i++) {
        string s = strs[i];
        sort(s.begin(), s.end());
        auto it = lut.find(s);
        if (it != lut.end()) {
            it->second.push_back(i);
        }
        else {
            vector<int> pos = {i};
            lut.insert(make_pair(s, pos));
        }
    }
    
    vector<string> res;
    for (auto it = lut.begin(); it != lut.end(); it++) {
        if (it->second.size() > 1) {
            for (int i : it->second) {
                res.push_back(strs[i]);
            }
        }
    }
    
    return res;
}


// 50 Pow(x, n)
double pow(double x, int n) {
    double res = 1;
    if (n == 0) return 1;
    bool flag = n < 0;
    n = abs(n);
    for(int i = 31; i >= 0; i--) {
        unsigned int t = 1 << i;
        if (t <= n) {
            n -= t;
            double step = x;
            for(int j = 0; j < i; j++) {
                step *= step;
            }
            res *= step;
        }
    }
    
    if (flag) res = double(1)/res;
    return res;
}

// 53 Maximum Subarray
int maxSubArray(int A[], int n) {
    int max = INT_MIN;
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += A[i];
        if (total > max)
            max = total;
        if (total <= 0)
            total = 0;
    }
    
    return max;
}

// 54 Spiral Matrix
vector<int> spiralOrder(vector<vector<int> > &matrix) {
    vector<int> sol;
    if (matrix.size() == 0) return sol;
    if (matrix[0].size() == 0)  return sol;
    
    int left = 0, top = 0;
    int right = matrix[0].size()-1;
    int bottom = matrix.size()-1;
    
    int count = (right + 1) * (bottom + 1);
    int finish = 0;
    
    while (true) {
        for (int i = left; i <= right; i++) {
            sol.push_back(matrix[top][i]);
            finish += 1;
        }
        if (finish == count) break;
        top += 1;
        for (int i = top; i <= bottom; i++) {
            sol.push_back(matrix[i][right]);
            finish += 1;
        }
        if (finish == count) break;
        right -= 1;
        for (int i = right; i >= left; i--) {
            sol.push_back(matrix[bottom][i]);
            finish += 1;
            
        }
        if (finish == count) break;
        bottom -= 1;
        for (int i = bottom; i >= top; i--) {
            sol.push_back(matrix[i][left]);
            finish += 1;
        }
        if (finish == count) break;
        left += 1;
    }
    
    return sol;
}


// 55 Jump Game
bool canJump(int A[], int n) {
    if (n==0) return false;
    if (n==1) return true;
    
    int l = 0;
    int max = A[l];
    for (int i = l+1; i <= max; i++) {
        if (max >= n-1)
            return true;
        if (i + A[i] > max)
            max = i + A[i];
    }
    return false;
}


// 59 Spiral Matrix II
vector<vector<int> > generateMatrix(int n) {
    vector<vector<int> > sol;
    if (n == 0) return sol;
    int x = 1;
    int l = 0, t = 0;
    int r = n-1, b = n-1;
    sol = vector<vector<int> >(n, vector<int>(n, 0));
    while(1) {
        for (int i = l; i <= r; i++) {
            sol[t][i] = x;
            x++;
        }
        t += 1;
        if (x > n*n) break;
        
        for (int i = t; i <= b; i++) {
            sol[i][r] = x;
            x++;
        }
        r -= 1;
        if (x > n*n) break;
        
        for (int i = r; i >= l; i--) {
            sol[b][i] = x;
            x++;
        }
        b -= 1;
        if (x > n*n) break;
        
        for (int i = b; i >= t; i--) {
            sol[i][l] = x;
            x++;
        }
        l += 1;
        if (x > n*n) break;
    }
    
    return sol;
}

// 60	Permutation Sequence
string getPermutation(int n, int k) {
    // build vector
    vector<int> v;
    for (int i = 1; i <= n; i++)
        v.push_back(i);
    
    // build factorial lut
    int fact[10];
    fill_n(fact, 10, 1);
    for (int i = 1; i < 10; i++)
        fact[i] = i * fact[i-1];
    
    string sol = "";
    while(n > 0) {
        int index = (k-1)/fact[n-1];
        sol += '0' + v[index];
        v.erase(v.begin() + index);
        k = (k-1)%fact[n-1] + 1;
        n--;
    }
    return sol;
}

// 61	Rotate List
ListNode *rotateRight(ListNode *head, int k) {
    // get list length
    int n = 0;
    ListNode *tmp = head;
    while (tmp != NULL) {
        tmp = tmp->next;
        n++;
    }
    if (n == 0 || k%n == 0)
        return head;
    
    // get actual move length
    k = k%n;
    
    // move list
    int stay = n - k;
    int i = 1;
    tmp = head;
    while(i < stay) {
        tmp = tmp->next;
        i++;
    }
    ListNode *newhead = tmp->next;
    tmp->next = NULL;
    tmp = newhead;
    while(tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = head;
    return newhead;
}

// 63	Unique Paths II
int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
    int m = obstacleGrid.size();
    int n = m > 0 ? obstacleGrid[0].size() : 0;
    if (m == 0 || n == 0)    return 0;
    vector<int> path(m + 1, 0);
    path[1] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < m+1; j++) {
            if (obstacleGrid[j-1][i] == 0) {
                path[j] += path[j-1];
            }
            else
                path[j] = 0;
        }
    }
    return path[m];
}

// 64	Minimum Path Sum
int dfsMinPath(int x, int y, vector<vector<int> > & grid, vector<vector<int> > &minLUT) {
    if (x == 0 && y == 0)   return grid[0][0];
    int v1 = INT_MAX;
    int v2 = INT_MAX;
    if (x - 1 >= 0) {
        if (minLUT[x-1][y] >= 0)
            v1 = minLUT[x-1][y];
        else {
            v1 = dfsMinPath(x-1, y, grid, minLUT);
            minLUT[x-1][y] = v1;
        }
    }
    if (y - 1 >= 0) {
        if (minLUT[x][y-1] >= 0)
            v2 = minLUT[x][y-1];
        else {
            v2 = dfsMinPath(x, y-1, grid, minLUT);
            minLUT[x][y-1] = v2;
        }
    }
    return grid[x][y] + min(v1, v2);
}

int minPathSum(vector<vector<int> > &grid) {
    int m = grid.size();
    int n = m > 0 ? grid[0].size() : 0;
    if (m == 0 || n == 0)    return 0;
    vector<vector<int> > minLUT(m, vector<int>(n, -1));
    return dfsMinPath(m-1, n-1, grid, minLUT);
}


// 69	Sqrt(x)
int sqrt(int x) {
    if (x == 0) return 0;
    if (x == 1) return 1;
    if (x < 0) return -1;
    unsigned int total = 0;
    for (int i = 15; i >= 0; i--) {
        unsigned int  tmp = total + (1 << i);
        if (tmp * tmp <= x) {
            total = tmp;
        }
    }
    
    
    return total;
}

// 73	Set Matrix Zeroes
void setZeroes(vector<vector<int> > &matrix) {
    unordered_set<int> zeroR, zeroC;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] == 0) {
                if (zeroR.find(i) == zeroR.end())
                    zeroR.insert(i);
                if (zeroC.find(j) == zeroC.end())
                    zeroC.insert(j);
            }
        }
    }
    
    for (auto it = zeroR.begin(); it != zeroR.end(); it++) {
        int i = *it;
        for (int j = 0; j < matrix[i].size(); j++) {
            matrix[i][j] = 0;
        }
    }
    
    for (auto it = zeroC.begin(); it != zeroC.end(); it++) {
        int j = *it;
        for (int i = 0; i < matrix.size(); i++) {
            matrix[i][j] = 0;
        }
    }
}

namespace _alternative {
    void setZeroes(vector<vector<int> > &matrix) {
        bool isRow0Zero = false;
        bool isCol0Zero = false;
        for (int j = 0; j < matrix[0].size(); j++)
            if (matrix[0][j] == 0) {
                isRow0Zero = true;
                break;
            }
        
        for (int i = 0; i < matrix.size(); i++) {
            if (matrix[i][0] == 0) {
                isCol0Zero = true;
                break;
            }
        }
        
        for (int i = 1; i < matrix.size(); i++) {
            for (int j = 1; j < matrix[i].size(); j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }
        
        // fill 0 to all rows except for the 1st row
        for (int i = 1; i < matrix.size(); i++) {
            if (matrix[i][0] == 0)
                fill_n(&matrix[i][1], matrix[i].size()-1, 0);
        }
        
        // fill 0 to all cols
        for (int j = 1; j < matrix[0].size(); j++) {
            if (matrix[0][j] == 0) {
                for (int i = 1; i < matrix.size(); i++) {
                    matrix[i][j] = 0;
                }
            }
        }
        
        if (isRow0Zero)
            fill_n(&matrix[0][0], matrix[0].size(), 0);
        
        if (isCol0Zero) {
            for (int i = 0; i < matrix.size(); i++) {
                matrix[i][0] = 0;
            }
        }
        
    }
}

// 74	Search a 2D Matrix
bool searchMatrix(vector<vector<int> > &matrix, int target){
    int m = matrix.size();
    int n = matrix[0].size();
    int r = -1;
    if (target < matrix[0][0] || target > matrix[m-1][n-1])
        return false;
    int a = 0, b = m-1;
    while (b>a) {
        int idx = (a+b)/2;
        int v = matrix[idx][0];
        if (target < v) {
            b = idx-1;
        }
        else if (target > v) {
            if (idx+1 < m) {
                if (target < matrix[idx+1][0]) {
                    r = idx;
                    break;
                }
                else
                    a = idx+1;
            }
        }
        else
            return true;
    }
    if (r == -1 && a == b) {
        r = a;
    }
    
    int i = 0, j = n-1;
    while (j >= i) {
        int idx = (i+j)/2;
        int v = matrix[r][idx];
        if (target < v) {
            j = idx-1;
        }
        else if (target > v) {
            i = idx+1;
        }
        else
            return true;
    }
    return false;
}

// 75	Sort Colors
void sortColors(int A[], int n) {
    int r = 0, w = 0, b = 0;
    for (int i = 0; i < n; i++) {
        if (A[i] == 0)  r++;
        else if (A[i] == 1) w++;
        else if (A[i] == 2) b++;
    }
    
    for (int i = 0; i < r; i++)
        A[i] = 0;
    for (int i = r; i < r + w; i++)
        A[i] = 1;
    for (int i = r+w; i < n; i++)
        A[i] = 2;
}

namespace _alternative {
    void sortColors(int A[], int n) {
        int i = -1, j = -1, k = -1;
        for (int idx = 0; idx < n; idx++) {
            if (A[idx] == 0) {
                A[++k] = 2;
                A[++j] = 1;
                A[++i] = 0;
            }
            else if (A[idx] == 1) {
                A[++k] = 2;
                A[++j] = 1;
            }
            else if (A[idx] == 2) {
                A[++k] = 2;
            }
        }
    }
}


// 77	Combinations
void combineDFS(vector<vector<int> > &sol, vector<int> &res, int l, int n, int k) {
    if (k==0) {
        sol.push_back(res);
    }
    else {
        if (n-l+1 < k)  return;
        for (int i = l; i <= n; i++) {
            res.push_back(i);
            combineDFS( sol, res, i+1, n, k-1);
            res.pop_back();
        }
    }
}

vector<vector<int> > combine(int n, int k) {
    vector<int> res;
    vector<vector<int> > sol;
    combineDFS(sol, res, 1, n, k);
    return sol;
}


// 78	Subsets
void subsetsDFS(vector<vector<int>> &sol, vector<int> &S, vector<int> &res, int l, int k) {
    if (k == 0) {
        sol.push_back(res);
    }
    else {
        for (int i = l; i < S.size(); i++) {
            res.push_back(S[i]);
            subsetsDFS(sol, S, res, i+1, k-1);
            res.pop_back();
        }
    }
}

vector<vector<int> > subsets(vector<int> &S) {
    sort(S.begin(), S.end());
    vector<int> res;
    vector<vector<int>> sol, ret;
    for (int k = 0; k <= S.size(); k++) {
        res.clear();
        sol.clear();
        subsetsDFS(sol, S, res, 0, k);
        ret.insert(ret.end(), sol.begin(), sol.end());
    }
    return ret;
}

// 79	Word Search
bool existDFS(vector<vector<char> > &b, vector<vector<bool> > &path, string& word, int index, int x, int y) {
    if (index >= word.size())   return true;
    char c = word[index];
    vector<pair<int, int> > p;
    p.push_back(make_pair(x-1,y));
    p.push_back(make_pair(x,y-1));
    p.push_back(make_pair(x+1,y));
    p.push_back(make_pair(x,y+1));
    for (pair<int, int> cell : p) {
        int i = cell.first;
        int j = cell.second;
        if (i>=0 && j>=0 && i < b.size() && j < b[0].size()) {
            if (b[i][j] == c && path[i][j]) {
                path[i][j] = false;
                bool ret = existDFS(b, path, word, index+1, i, j);
                path[i][j] = true;
                if (ret)    return true;
            }
        }
    }
    return false;
}

bool exist(vector<vector<char> > &board, string word) {
    int m = board.size();
    int n = board[0].size();
    vector<vector<bool> > path(m, vector<bool>(n, true));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            char c = board[i][j];
            if (c == word[0]) {
                path[i][j] = false;
                bool ret = existDFS(board, path, word, 1, i, j);
                path[i][j] = true;
                if (ret)    return true;
            }
        }
    }
    return false;
    
}


// 81	Search in Rotated Sorted Array II
bool searchRecursive(int A[], int l, int r, int target) {
    if (l > r) return false;
    int mid = l + (r-l)/2;
    if (A[mid] == target)   return true;
    if (A[l] < A[mid]) {
        if (A[l] <= target && target <= A[mid]) {
            return searchRecursive(A, l, mid-1, target);
        }
        else {
            return searchRecursive(A, mid+1, r, target);
        }
    }
    else if (A[mid] < A[r]) {
        if (A[mid] <= target && target <= A[r]) {
            return searchRecursive(A, mid+1, r, target);
        }
        else {
            return searchRecursive(A, l, mid-1, target);
        }
    }
    else {
        bool ret = false;
        ret = searchRecursive(A, l, mid-1, target);
        if (!ret)
            ret = searchRecursive(A, mid+1, r, target);
        return ret;
    }
}
bool search(int A[], int n, int target) {
    return searchRecursive(A, 0, n-1, target);
}


// 82	Remove Duplicates from Sorted List II
ListNode *deleteDuplicates(ListNode *head) {
    if (!head)  return head;
    ListNode *vhead = new ListNode(0);
    vhead->next = head;
    ListNode *last = vhead;
    ListNode *tmp = head;
    ListNode *tmp2 = vhead;
    int cur = head->val;
    int count = 0;
    while (tmp != NULL) {
        if (tmp->val == cur) {
            count += 1;
            tmp2 = tmp;
            tmp = tmp->next;
        }
        else {
            if (count == 1) {
                last = tmp2;
                cur = tmp->val;
                count = 1;
                tmp2 = tmp;
                tmp = tmp->next;
            }
            else {
                last->next = tmp;
                cur = tmp->val;
                count = 1;
                tmp2 = tmp;
                tmp = tmp->next;
            }
        }
    }
    if (count > 1) {
        last->next = tmp;
    }
    
    head = vhead->next;
    return head;
}

// 86	Partition List
ListNode *partition(ListNode *head, int x) {
    if (!head) return head;
    ListNode *head1 = NULL;
    ListNode *head2 = NULL;
    ListNode *tmp1 = head1;
    ListNode *tmp2 = head2;
    ListNode *tmp = head;
    while(tmp != NULL) {
        if (tmp->val < x) {
            if (!head1) {
                head1 = tmp;
                tmp1 = head1;
            }
            else {
                tmp1->next = tmp;
                tmp1 = tmp1->next;
            }
        }
        else {
            if (!head2) {
                head2 = tmp;
                tmp2 = head2;
            }
            else {
                tmp2->next = tmp;
                tmp2 = tmp2->next;
            }
        }
        tmp = tmp->next;
    }
    
    if (head1) {
        tmp1->next = head2;
        if (tmp2) {
            tmp2->next = NULL;
        }
        return head1;
    }
    else {
        if (tmp2) {
            tmp2->next = NULL;
        }
        return head2;
    }
}

// 89	Gray Code
void genGrayCode(vector<int> &sol, int n) {
    if (n == 0) sol.push_back(0);
    else {
        genGrayCode(sol, n-1);
        vector<int> tmp;
        int v = 1 << (n-1);
        for (int i = sol.size()-1; i>=0; i--) {
            int res = sol[i] | v;
            tmp.push_back(res);
        }
        sol.insert(sol.end(), tmp.begin(), tmp.end());
    }
}

vector<int> grayCode(int n) {
    vector<int> sol;
    genGrayCode(sol, n);
    return sol;
}


// 90	Subsets II
void subsetsWithDupDFS(vector<int> &S, vector<vector<int>> &sol, vector<int> &res, int n, int l) {
    if (n == 0)
        sol.push_back(res);
    else {
        for (int i = l; i < S.size(); i++) {
            res.push_back(S[i]);
            subsetsWithDupDFS(S, sol, res, n-1, i+1);
            res.pop_back();
            while (i+1 < S.size() && S[i+1] == S[i])
                i += 1;
        }
    }
}

vector<vector<int> > subsetsWithDup(vector<int> &S) {
    sort(S.begin(), S.end());
    
    vector<vector<int>> sol;
    
    for (int i = 0; i <= S.size(); i++) {
        vector<int> res;
        subsetsWithDupDFS(S, sol, res, i, 0);
    }
    
    return sol;
}

// 91	Decode Ways
void numDecodingsRecur(set<int> &os, set<int> &ts, int cur, int n, int &total) {
    if (cur == n)
        total += 1;
    else {
        if (os.find(cur) != os.end()) {
            numDecodingsRecur(os, ts, cur + 1, n, total);
        }
        if (ts.find(cur) != ts.end()) {
            numDecodingsRecur(os, ts, cur + 2, n, total);
        }
    }
}

int numDecodings(string s) {
    if (s.size() == 0)
        return 0;
    if (s[0] == '0')
        return 0;
    
    vector<int> ways(s.size(), 0);
    ways[0] = 1;
    for (int i = 1; i < s.size(); i++) {
        // 1. one step
        bool canOneStep = false;
        int v = s[i] - '0';
        if (v > 0 && v < 10) {
            canOneStep = true;
        }
        
        // 2. two steps
        bool canTwoStep = false;
        int x = s[i-1]-'0';
        int y = s[i] - '0';
        if (x > 0 && x < 3 && y >= 0 && y < 10 && x * 10 + y <= 26) {
            canTwoStep = true;
        }
        
        // judge
        if (canOneStep)
            ways[i] += ways[i-1];
        if (canTwoStep) {
            if (i-2>=0)
                ways[i] += ways[i-2];
            else
                ways[i] += 1;
        }
    }
    
    return ways[s.size()-1];
    
}

// 92	Reverse Linked List II	26.2%	Medium
ListNode *reverseBetween(ListNode *head, int m, int n) {
    if (!head)  return head;
    if (m == n) return head;
    ListNode *a = NULL;
    ListNode *b = NULL;
    ListNode *preva = NULL;
    ListNode *nextb = NULL;
    ListNode *tmp = head;
    ListNode *prevtmp = NULL;
    int i = 1;
    while (tmp != NULL) {
        if (i < m || i > n) {
            i+=1;
            prevtmp = tmp;
            tmp = tmp->next;
        }
        else {
            if (i == m) {
                a = tmp;
                preva = prevtmp;
            }
            else if (i == n) {
                b = tmp;
                nextb = tmp->next;
            }
            
            ListNode *x = prevtmp;
            prevtmp = tmp;
            tmp = tmp->next;
            prevtmp->next = x;
            i+=1;
        }
    }
    
    if (preva)
        preva->next = b;
    else
        head = b;
    
    a->next = nextb;
    return head;
}

// 93	Restore IP Addresses
void restoreRecur(string s, int n, vector<string> &sol, vector<string> &res) {
    if (n <= (int)s.size() && (int)s.size() <= 3*n) {
        if (n == 1 && stoi(s) >= 0 && stoi(s) <= 255) {
            if (s.size() > 1 && s[0] == '0')    return;
            
            string asol = "";
            for (string part : res) {
                asol += part;
                asol += '.';
            }
            asol += s;
            sol.push_back(asol);
        }
        else {
            for (int i = 0; i < 3; i++) {
                int restLen = (int)s.size()-i-1;
                if (restLen >= 0) {
                    string tmp = s.substr(0, i+1);
                    if (stoi(tmp) >= 0 && stoi(tmp) <= 255) {
                        
                        if (tmp.size() > 1 && tmp[0] == '0')    continue;
                        
                        res.push_back(tmp);
                        restoreRecur(s.substr(i+1, s.size()-i-1), n-1, sol, res);
                        res.pop_back();
                    }
                }
            }
        }
    }
}

vector<string> restoreIpAddresses(string s) {
    vector<string> sol;
    vector<string> res;
    restoreRecur(s, 4, sol, res);
    return sol;
}


// 94	Binary Tree Inorder Traversal
void inorderRecur(vector<int> &sol, TreeNode *node) {
    if (node) {
        if (node->left) {
            inorderRecur(sol, node->left);
        }
        sol.push_back(node->val);
        if (node->right) {
            inorderRecur(sol, node->right);
        }
    }
}

vector<int> inorderTraversal(TreeNode *root) {
    vector<int> sol;
    inorderRecur(sol, root);
    return sol;
}

namespace _alternative {
    vector<int> inorderTraversal(TreeNode *root) {
        // Morris Traversal
        vector<int> sol;
        while(root) {
            if (!root->left) {
                sol.push_back(root->val);
                root = root->right;
            }
            else {
                TreeNode *pre = root->left;
                while(pre->right && pre->right != root) {
                    pre = pre->right;
                }
                if (pre->right == NULL) {
                    pre->right = root;
                    root = root->left;
                }
                else {
                    pre->right = NULL;
                    sol.push_back(root->val);
                    root = root->right;
                }
            }
        }
        return sol;
    }
}

// 95	Unique Binary Search Trees II
vector<TreeNode *> generateSubTrees(int l, int r) {
    vector<TreeNode *> list;
    if (l > r) {
        list.push_back(NULL);
    }
    else if (l == r) {
        TreeNode *node = new TreeNode(l);
        list.push_back(node);
    }
    else {
        for (int i = l; i <= r; i++) {
            vector<TreeNode *> leftset = generateSubTrees(l, i-1);
            vector<TreeNode *> rightset = generateSubTrees(i+1, r);
            for (TreeNode *left : leftset) {
                for (TreeNode *right : rightset) {
                    TreeNode *node = new TreeNode(i);
                    node->left = left;
                    node->right = right;
                    list.push_back(node);
                }
            }
        }
    }
    
    return list;
}

vector<TreeNode *> generateTrees(int n) {
    return generateSubTrees(1, n);
}

// 96	Unique Binary Search Trees
int findCombinationBST(int A[], int n) {
    if (A[n] != -1) return A[n];
    else {
        int total = 0;
        for (int i = 0; i < n; i++) {
            int l = findCombinationBST(A, i);
            int r = findCombinationBST(A, n-i-1);
            total += l * r;
        }
        A[n] = total;
        return total;
    }
}

int numTrees(int n) {
    int *lut = new int[n+1];
    fill_n(lut, n+1, -1);
    lut[0] = 1;
    lut[1] = 1;
    lut[2] = 2;
    lut[3] = 5;
    return findCombinationBST(lut, n);
}

// 98	Validate Binary Search Tree
bool isValidBSTRecur(TreeNode *node, int64_t min, int64_t max) {
    bool res = true;
    if (node) {
        int64_t v = (int64_t)node->val;
        if (v <= min || v >= max)   return false;
        res = isValidBSTRecur(node->left, min, v);
        if (res)
            res = isValidBSTRecur(node->right, v, max);
    }
    return res;
}

bool isValidBST(TreeNode *root) {
    return isValidBSTRecur(root, INT_MIN-1LL, INT_MAX+1LL);
}

// 103	Binary Tree Zigzag Level Order Traversal
vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
    vector<vector<int>> sol;
    vector<TreeNode *> next, cur;
    if (root) {
        next.push_back(root);
        while(!next.empty()) {
            vector<int> vals;
            for (auto node : next) {
                vals.push_back(node->val);
                if (node->left)
                    cur.push_back(node->left);
                if (node->right)
                    cur.push_back(node->right);
            }
            sol.push_back(vals);
            next.clear();
            next = cur;
            cur.clear();
        }
        
        for (int i = 1; i < sol.size(); i+=2) {
            std::reverse(sol[i].begin(), sol[i].end());
        }
    }
    return sol;
}

// 105	Construct Binary Tree from Preorder and Inorder Traversal
TreeNode *buildSubTree(vector<int> &pre, vector<int> &in, int pl, int pr, int il, int ir) {
    if (pl > pr || il > ir) {
        return NULL;
    }
    else if (pl == pr) {
        TreeNode *node = new TreeNode(pre[pl]);
        return node;
    }
    else {
        int val = pre[pl];
        TreeNode *node = new TreeNode(val);
        int index = -1;
        for (int i = il; i <= ir; i++) {
            if (in[i] == val) {
                index = i;
                break;
            }
        }
        int sl = index-il;
        int sr = ir-index;
        node->left = buildSubTree(pre, in, pl+1, pl+sl, il, index-1);
        node->right = buildSubTree(pre, in, pl+sl+1, pr, index+1, ir);
        return node;
    }
}

TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
    return buildSubTree(preorder, inorder, 0, (int)preorder.size()-1, 0, (int)inorder.size()-1);
}


// 106	Construct Binary Tree from Inorder and Postorder Traversal
TreeNode *buildTreeDFS(vector<int> &in, vector<int> &po, int il, int ir, int pl, int pr) {
    if (il > ir)    return NULL;
    else if (il == ir) {
        TreeNode *node = new TreeNode(in[il]);
        return node;
    }
    else {
        int val = po[pr];
        int index = -1;
        for (int i = il; i <= ir; i++) {
            if (in[i] == val) {
                index = i;
                break;
            }
        }
        
        TreeNode *node = new TreeNode(val);
        int sizel = index-il;
        int sizer = ir-index;
        node->left = buildTreeDFS(in, po, il, index-1, pl, pl+sizel-1);
        node->right = buildTreeDFS(in, po, index+1, ir, pr-sizer, pr-1);
        return node;
    }
}

TreeNode *buildTree106(vector<int> &inorder, vector<int> &postorder) {
    return buildTreeDFS(inorder, postorder, 0, (int)inorder.size()-1, 0, (int)postorder.size()-1);
}

namespace _alternative {
    
    TreeNode *buildTree106(vector<int> &inorder, vector<int> &postorder) {
        if (!inorder.size())    return NULL;
        
        stack<TreeNode *> st;
        TreeNode *root, *p;
        root = new TreeNode(postorder.back());
        st.push(root);
        postorder.pop_back();
        while (1) {
            if (inorder.back() == st.top()->val) {
                p = st.top();
                st.pop();
                inorder.pop_back();
                if (inorder.size() == 0)    break;
                if (st.size() && inorder.back() == st.top()->val) continue;
                TreeNode *node = new TreeNode(postorder.back());
                p->left = node;
                st.push(node);
                postorder.pop_back();
            }
            else {
                TreeNode *node = new TreeNode(postorder.back());
                st.top()->right = node;
                st.push(node);
                postorder.pop_back();
            }
        }
        
        return root;
    }
}

// 109	Convert Sorted List to Binary Search Tree
TreeNode *sortedListToBSTRecur(ListNode *head, int size) {
    if (size == 0)  return NULL;
    else if (size == 1) {
        TreeNode *node = new TreeNode(head->val);
        return node;
    }
    else {
        int half = size/2+1;
        int count = 1;
        auto tmp = head;
        while (count < half) {
            tmp = tmp->next;
            count += 1;
        }
        int lsize = half - 1;
        int rsize = size - half;
        TreeNode *node = new TreeNode(tmp->val);
        node->left = sortedListToBSTRecur(head, lsize);
        node->right = sortedListToBSTRecur(tmp->next, rsize);
        return node;
    }
}

TreeNode *sortedListToBST(ListNode *head) {
    if (!head) return NULL;
    auto tmp = head;
    int size = 1;
    while (tmp->next != NULL) {
        tmp = tmp->next;
        size += 1;
    }
    return sortedListToBSTRecur(head, size);
}


namespace _alternative {
    
    TreeNode *dfsConstructBST(ListNode **list, int size) {
        if (size == 0)  return NULL;
        TreeNode *node = new TreeNode(0);
        node->left = dfsConstructBST(list, size/2);
        node->val = (*list)->val;
        *list = (*list)->next;
        node->right = dfsConstructBST(list, size - size/2 - 1);
        return node;
    }
    
    TreeNode *sortedListToBST(ListNode *head) {
        if (!head) return NULL;
        auto tmp = head;
        int size = 1;
        while (tmp->next != NULL) {
            tmp = tmp->next;
            size += 1;
        }
        return dfsConstructBST(&head, size);
    }
}


// 114	Flatten Binary Tree to Linked List
void flatten(TreeNode *root) {
    TreeNode *node = root;
    while (node != NULL) {
        if (!node->left) {
            node = node->right;
            continue;
        }
        TreeNode *tmp = node->left;
        while (tmp->right) tmp = tmp->right;
        tmp->right = node->right;
        node->right = node->left;
        node->left = NULL;
        node = node->right;
    }
}


// 116	Populating Next Right Pointers in Each Node
void connect(TreeLinkNode *root) {
    if (root) {
        vector<TreeLinkNode *> next;
        vector<TreeLinkNode *> cur;
        next.push_back(root);
        while (!next.empty()) {
            for (int i = 0; i < next.size(); i++) {
                TreeLinkNode *node = next[i];
                if (i+1 < next.size())
                    node->next = next[i+1];
                if (node->left)
                    cur.push_back(node->left);
                if (node->right)
                    cur.push_back(node->right);
            }
            next.clear();
            next = cur;
            cur.clear();
        }
    }
}

namespace _alternative {
    void connect(TreeLinkNode *root) {
        TreeLinkNode *head = root;
        TreeLinkNode *cur = NULL;
        TreeLinkNode *pre = NULL;
        while (head) {
            cur = head;
            head = pre = NULL;
            while (cur) {
                
                if (cur->left) {
                    if (pre) {
                        pre = pre->next = cur->left;
                    }
                    else {
                        head = pre = cur->left;
                    }
                }
                
                if (cur->right) {
                    pre = pre->next = cur->right;
                }
                cur = cur->next;
            }
        }
    }
}

// 120	Triangle
int minimumTotal(vector<vector<int> > &triangle) {
    if (!triangle.size())   return 0;
    vector<int> res = triangle[triangle.size()-1];
    for (int j = triangle.size()-1; j >= 1; j--) {
        for (int i = 0; i < triangle[j-1].size(); i++) {
            res[i] = triangle[j-1][i] + min(res[i], res[i+1]);
        }
    }
    return res[0];
}

// 122	Best Time to Buy and Sell Stock II
int maxProfit(vector<int> &prices) {
    int profit = 0;
    for (int i = 1; i < prices.size(); i++) {
        int income = prices[i] - prices[i-1];
        if (income > 0) {
            profit += income;
        }
    }
    return profit;
}

// 127	Word Ladder
unordered_set<string> genNext(string word, unordered_set<string> &tested, unordered_set<string> &dict) {
    unordered_set<string> next;
    for (int i = 0; i < word.size(); i++) {
        for (int j = 0; j < 26; j++) {
            string s = word;
            s[i] = 'a' + j;
            if (dict.find(s) != dict.end() && tested.find(s) == tested.end())
                next.insert(s);
        }
    }
    return next;
}

int ladderLength(string start, string end, unordered_set<string> &dict) {
    unordered_set<string> cur, next, tested;
    int length = 1;
    tested.insert(start);
    next = genNext(start, tested, dict);
    while(!next.empty()) {
        if (next.find(end) != next.end())
            return length + 1;
        for (string word : next) {
            tested.insert(word);
            decltype(cur) wordNext = genNext(word, tested, dict);
            cur.insert(wordNext.begin(), wordNext.end());
        }
        next.clear();
        next = cur;
        cur.clear();
        length += 1;
    }
    return 0;
}

// 130	Surrounded Regions
struct PairHash {
public:
    size_t operator()(const std::pair<int, int> &x) const {
        return x.first * 10000 + x.second;
    }
};

void solve(vector<vector<char>> &board) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] == 'O') {
                unordered_set<pair<int, int>, PairHash> next, cur, res;
                next.insert(make_pair(i, j));
                res.insert(next.begin(), next.end());
                bool surround = true;
                if (i == 0 || j == 0 || i == board.size()-1 || j == board[i].size()-1)
                    surround = false;
                while(!next.empty()) {
                    for (auto pos : next) {
                        // do 4 directions tests
                        int x = pos.first;
                        int y = pos.second;
                        // UP
                        if (x - 1 >= 0 && board[x-1][y] == 'O' && res.find(make_pair(x-1, y)) == res.end()) {
                            if (x - 1 == 0) surround = false;
                            cur.insert(make_pair(x-1,y));
                        }
                        // DOWN
                        if (x + 1 < board.size() && board[x+1][y] == 'O' && res.find(make_pair(x+1, y)) == res.end()) {
                            if (x + 1 == board.size()-1) surround = false;
                            cur.insert(make_pair(x+1,y));
                        }
                        // Left
                        if (y - 1 >= 0 && board[x][y-1] == 'O' && res.find(make_pair(x, y-1)) == res.end()) {
                            if (y - 1 == 0) surround = false;
                            cur.insert(make_pair(x,y-1));
                        }
                        // right
                        if (y + 1 < board[x].size() && board[x][y+1] == 'O' && res.find(make_pair(x, y+1)) == res.end()) {
                            if (y+1 == board[x].size()-1) surround = false;
                            cur.insert(make_pair(x,y+1));
                        }
                    }
                    next.clear();
                    next = cur;
                    cur.clear();
                    res.insert(next.begin(), next.end());
                }
                if (surround) {
                    for (auto pos : res) {
                        board[pos.first][pos.second] = 'X';
                    }
                }
                else {
                    for (auto pos : res) {
                        board[pos.first][pos.second] = '-';
                    }
                }
            }
        }
    }
    
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] == '-') board[i][j] = 'O';
        }
    }
}


// 131	Palindrome Partitioning
bool isPalindromeHelper(string &s, int l, int r) {
    while (l < r) {
        if (s[l] != s[r])
            return false;
        l++;
        r--;
    }
    return true;
}

void partitionDFS(string &s, int l, vector<vector<string> > &sol, vector<string> &res) {
    int remainSize = s.size()-l;
    if (remainSize <= 0 && res.size() > 0) {
        sol.push_back(res);
    }
    else {
        for (int i = 1; i <= remainSize; i++) {
            if (isPalindromeHelper(s, l, l+i-1)) {
                res.push_back(s.substr(l, i));
                partitionDFS(s, l+i, sol, res);
                res.pop_back();
            }
        }
    }
}

vector<vector<string>> partition(string s) {
    vector<vector<string>> sol;
    vector<string> res;
    partitionDFS(s, 0, sol, res);
    return sol;
}



// 133 Clone Graph
typedef UndirectedGraphNode UGN;
UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
    if (!node)   return nullptr;
    
    unordered_map<int, vector<int> > relationship;
    vector<UGN*> next, cur;
    next.push_back(node);
    
    // BFS building relationship
    while(!next.empty()) {
        for (UGN *anode : next) {
            if (relationship.find(anode->label) != relationship.end())
                continue;
            
            vector<int> nbrs;
            relationship.insert(make_pair(anode->label, nbrs));
            auto it = relationship.find(anode->label);
            
            for (UGN *n : anode->neighbors) {
                int id = n->label;
                it->second.push_back(id);
                if (relationship.find(id) == relationship.end()) {
                    cur.push_back(n);
                }
            }
        }
        next.clear();
        next = cur;
        cur.clear();
    }
    
    // make relationship to be fully copied graph
    // initialize all copied nodes
    UGN *root = nullptr;
    unordered_map<int, UGN*> lut;
    for (auto it = relationship.begin(); it != relationship.end(); it++) {
        int label = it->first;
        UGN *copy = new UGN(label);
        if (label == node->label)    root = copy;
        lut.insert(make_pair(label, copy));
    }
    
    // build actual relationship of all copied nodes
    for (auto it = relationship.begin(); it != relationship.end(); it++) {
        int label = it->first;
        UGN *copy = lut.find(label)->second;
        for (int id : it->second) {
            auto itLocator = lut.find(id);
            copy->neighbors.push_back(itLocator->second);
        }
    }
    
    return root;
    
}


// 134	Gas Station
int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
    int n = gas.size();
    vector<int> net(n, 0);
    int total = 0;
    int index = 0;
    for (int i = 0; i < n; i++) {
        net[i] = gas[i] - cost[i];
        total += net[i];
    }
    if (total < 0)  return -1;
    total = 0;
    for (int i = 0; i < n; i++) {
        total += net[i];
        if (total < 0) {
            total = 0;
            index = i+1;
        }
    }
    return index;
}

// 137	Single Number II
int singleNumber(int A[], int n) {
    // count occurences of 1s for each bit
    int ec1 = 0, ec2 = 0, ec3 = 0;
    for (int i = 0; i < n; i++) {
        ec3 = ec2 & A[i];
        ec2 = (ec2 | (ec1 & A[i])) & (~ec3);
        ec1 = (ec1 | A[i]) & (~ec2) & (~ec3);
    }
    return ec1;
}


// 139	Word Break, DFS, 6 ms
bool wordBreakRecur(string s, unordered_set<string> &dict, set<int> &len) {
    if (dict.find(s) != dict.end()) {
        return true;
    }
    else {
        for (auto it = len.begin(); it != len.end(); it++) {
            int subSize = *it;
            if (subSize <= s.size()) {
                string sub = s.substr(0, subSize);
                if (dict.find(sub) != dict.end()) {
                    bool found = wordBreakRecur(s.substr(subSize, s.size()-subSize), dict, len);
                    if (found)
                        return true;
                }
            }
        }
        return false;
    }
}

bool wordBreak(string s, unordered_set<string> &dict) {
    set<int> len;
    unordered_set<char> dictchars;
    
    for (auto word : dict) {
        for (char c : word) {
            dictchars.insert(c);
        }
        int size = word.size();
        len.insert(size);
    }
    
    for (char c : s) {
        if (dictchars.find(c) == dictchars.end())   return false;
    }
    
    return wordBreakRecur(s, dict, len);
}

// 141	Linked List Cycle
bool hasCycle(ListNode *head) {
    if (!head) return false;
    ListNode *t1 = head;
    ListNode *t2 = head->next;
    while (t1 && t2) {
        if (t1 == t2) {
            return true;
        }
        t1 = t1->next;
        t2 = t2->next;
        if (!t2)    return false;
        else
            t2 = t2->next;
    }
    return false;
}

// 142	Linked List Cycle II
ListNode *detectCycle(ListNode *head) {
    if (!head)  return nullptr;
    auto t1 = head;
    auto t2 = head->next;
    ListNode *p = nullptr;
    while (t1 && t2) {
        if (t1 == t2) {
            p = t1;
            break;
        }
        t1 = t1->next;
        t2 = t2->next;
        if (!t2)    return nullptr;
        else t2 = t2->next;
    }
    if (!p) return nullptr;
    
    // test cycles
    int cycle = 1;
    t1 = p;
    t2 = p->next;
    while (t1 != t2) {
        t1 = t1->next;
        t2 = t2->next->next;
        cycle++;
    }
    
    
    t1 = head;
    t2 = t1;
    for (int i = 0; i < cycle; i++) {
        t2 = t2->next;
    }
    
    while (t1 != t2) {
        t1 = t1->next;
        t2 = t1;
        for (int i = 0; i < cycle; i++) {
            t2 = t2->next;
        }
    }
    
    return t1;
}

// 142
namespace _alternative {
    ListNode *detectCycle(ListNode *head) {
        if (head == NULL || head->next == NULL) return NULL;
        
        ListNode* firstp = head;
        ListNode* secondp = head;
        bool isCycle = false;
        
        while(firstp != NULL && secondp != NULL) {
            firstp = firstp->next;
            if (secondp->next == NULL) return NULL;
            secondp = secondp->next->next;
            if (firstp == secondp) { isCycle = true; break; }
        }
        
        if(!isCycle) return NULL;
        firstp = head;
        while( firstp != secondp) {
            firstp = firstp->next;
            secondp = secondp->next;
        }
        
        return firstp;
    }
}

// 143	Reorder List
void reorderList(ListNode *head) {
    auto p = head;
    vector<ListNode *>nodes;
    
    while (p) {
        nodes.push_back(p);
        p = p->next;
    }
    
    if (nodes.size() < 3)   return;
    
    int tailI = -1;
    int tailJ = -1;
    for (int i = 0; i < nodes.size(); i++) {
        int j = nodes.size() - i - 1;
        if (i < j) {
            nodes[i]->next = nodes[j];
            nodes[j]->next = nodes[i+1];
            tailI = i;
            tailJ = j;
        }
        else {
            break;
        }
    }
    
    if (nodes.size()%2) nodes[tailI+1]->next = nullptr;
    else nodes[tailJ]->next = nullptr;
}

// 144	Binary Tree Preorder Traversal
vector<int> preorderTraversal(TreeNode *root) {
    vector<int> sol;
    TreeNode *cur = root, *prev = nullptr;
    while (cur != nullptr) {
        if (cur->left == nullptr) {
            sol.push_back(cur->val);
            cur = cur->right;
        }
        else {
            prev = cur->left;
            while(prev->right && prev->right != cur) {
                prev = prev->right;
            }
            if (prev->right == nullptr) {
                sol.push_back(cur->val);
                prev->right = cur;
                cur = cur->left;
            }
            else {
                prev->right = nullptr;
                cur = cur->right;
            }
        }
    }
    return sol;
}
