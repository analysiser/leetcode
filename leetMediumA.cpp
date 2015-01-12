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