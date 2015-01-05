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



