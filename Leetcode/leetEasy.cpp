//
//  leetEasy.cpp
//  Leetcode
//
//  Created by Xiao Li on 12/26/14.
//  Copyright (c) 2014 Xiao. All rights reserved.
//

#include "leetEasy.h"


namespace _easy {
    
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        
        // write your code here
        if (!l1) {
            return l2;
        }
        if (!l2) {
            return l1;
        }
        ListNode *head = nullptr;
        ListNode *cur = nullptr;
        
        while (l1 && l2) {
            ListNode *tmp = nullptr;
            if (l1->val <= l2->val) {
                tmp = l1;
                l1 = l1->next;
                tmp->next = nullptr;
            }
            else {
                tmp = l2;
                l2 = l2->next;
                tmp->next = nullptr;
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
    
    int majorityElement(vector<int> &num)
    {
        unordered_map<int, int> amap;
        int cutoff = (int)num.size()/2;
        for (int i:num)
        {
            auto it = amap.find(i);
            if (it == amap.end()) {
                amap.insert(pair<int, int>(i, 1));
            }
            else {
                it->second += 1;
                
                if (it->second > cutoff)
                    return it->first;
            }
        }
        
        return num[0];
    }
    
    string convertToTitle(int n) {
        
        return n == 0 ? "" : convertToTitle((n - 1) / 26) + (char) ((n - 1) % 26 + 'A') ;
    }
    
    int compareVersion(string version1, string version2) {
        
        int i1 = 0, i2 = 0;
        while (i1 < version1.length())
        {
            int v = version1[i1] - '0';
            if ((v > 0 && v < 10) || version1[i1] == '.')
                break;
            i1++;
        }
        
        while (i2 < version2.length())
        {
            int v = version2[i2] - '0';
            if ((v > 0 && v < 10) || version2[i2] == '.')
                break;
            i2++;
        }
        
        int iv1 = 0, iv2 = 0;
        while (i1 < version1.length() || i2 < version2.length())
        {
            while (i1 < version1.length())
            {
                int v = version1[i1] - '0';
                if (v < 0 || v > 9)
                    break;
                else {
                    iv1 *= 10;
                    iv1 += v;
                    
                }
                i1++;
            }
            while (i2 < version2.length())
            {
                int v = version2[i2] - '0';
                if (v < 0 || v > 9)
                    break;
                else {
                    iv2 *= 10;
                    iv2 += v;
                    
                }
                i2++;
            }
            
            if (iv1 > iv2)  return 1;
            else if (iv1 < iv2) return -1;
            else {
                iv1 = 0;
                iv2 = 0;
                i1++;
                i2++;
            }
            
        }
        
        if (iv1 > iv2)  return 1;
        else if (iv1 < iv2) return -1;
        else return 0;
    }
    
    
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        
        if (!headA || !headB)   return nullptr;
        if (headA == headB) return headA;
        
        ListNode *end = nullptr;
        
        ListNode *pa = headA;
        ListNode *pb = headB;
        while (true)
        {
            pa = headA;
            pb = headB;
            
            while (pa->next)
            {
                if (pa->next == end)
                    break;
                pa = pa->next;
            }
            while (pb->next)
            {
                if (pb->next == end)
                    break;
                pb = pb->next;
            }
            
            if (pa != pb)
            {
                if (end == nullptr) return nullptr;
                else return end;
            }
            else {
                end = pa;
            }
        }
        return nullptr;
    }
    
    
    
    // New solution
    class MinStack {
    public:
        void push(int x) {
            st.push(x);
            if (minst.empty()) {
                minst.push(make_pair(x, 1));
            }
            else {
                auto &minP = minst.top();
                if (x == minP.first) {
                    minP.second += 1;
                }
                else if (x < minP.first) {
                    minst.push(make_pair(x, 1));
                }
            }
        }
        
        void pop() {
            int num = st.top();
            st.pop();
            if (num == minst.top().first) {
                minst.top().second -= 1;
                if (minst.top().second == 0) {
                    minst.pop();
                }
            }
        }
        
        int top() {
            return st.top();
        }
        
        int getMin() {
            return minst.top().first;
        }
    private:
        stack<int> st;
        stack<pair<int, int>> minst;
    };
    
    // Old solution with Linked List
//    class MinStack {
//    public:
//        
//        void push(int x) {
//            if (head && (head->size < nodesize))
//            {
//                head->push(x);
//            }
//            else
//            {
//                Node *tmp = new Node(x);
//                tmp->next = head;
//                head = tmp;
//            }
//        }
//        
//        void pop() {
//            if (head)
//            {
//                head->pop();
//                if (head->size <= 0)
//                {
//                    Node *tmp = head;
//                    head = head->next;
//                    delete tmp;
//                }
//            }
//        }
//        
//        int top() {
//            if (head)
//            {
//                return head->top();
//            }
//            return 0;
//        }
//        
//        int getMin() {
//            if (head)
//            {
//                int min = INT_MAX;
//                Node *tmp = head;
//                while (tmp)
//                {
//                    if (tmp->min < min)
//                        min = tmp->min;
//                    
//                    tmp = tmp->next;
//                }
//                return min;
//            }
//            return 0;
//        }
//        
//    private:
//        static const int nodesize = 100;
//        struct Node {
//            int v[nodesize];
//            Node *next;
//            int size;
//            int min;
//            
//            Node(int x) {
//                size = 0;
//                min = x;
//                push(x);
//                next = nullptr;
//            }
//            void push(int x) {
//                v[size++] = x;
//                if (x < min)    min = x;
//            }
//            void pop() {
//                if (min == top())
//                {
//                    min = v[0];
//                    for (int i = 1; i < size - 1; i++)
//                    {
//                        if (v[i] < min) min = v[i];
//                    }
//                }
//                size--;
//            }
//            int top() {
//                if (size > 0)
//                {
//                    return v[size-1];
//                }
//                return 0;
//            }
//        };
//        
//        Node *head = nullptr;
//    };
    
    
    vector<vector<int> > levelOrderBottom(TreeNode *root) {
        vector<vector<int> > ret;
        deque<vector<int> > tmp;
        vector<TreeNode *> cur;
        vector<TreeNode *> next;
        
        if (!root)  return ret;
        
        next.push_back(root);
        
        while (!next.empty())
        {
            vector<int> level;
            for (TreeNode *node : next)
            {
                level.push_back(node->val);
                if (node->left)
                    cur.push_back(node->left);
                if (node->right)
                    cur.push_back(node->right);
            }
            tmp.push_front(level);
            next.clear();
            next = cur;
            cur.clear();
        }
        
        ret = vector<vector<int>>(tmp.begin(), tmp.end());
        
        return ret;
    }
    
    string countAndSay(int n) {
        string ret = "";
        if (n == 0) return ret;
        if (n == 1) return "1";
        if (n == 2) return "11";
        
        ret = "11";
        string temp = "";
        for (int i = 3; i <= n; i++)
        {
            int j = 0;
            int k = 1;
            
            while (j < ret.length())
            {
                while (ret[j] == ret[k]) {
                    k++;
                }
                temp += to_string(k-j);
                temp += ret[j];
                j = k;
                k = j + 1;
            }
            
            ret = temp;
            temp = "";
        }
        
        return ret;
        
    }
    
    void getNext(char *p, int next[])
    {
        int pLen = (int)strlen(p);
        next[0] = -1;
        int k = -1;
        int j = 0;
        while (j < pLen - 1) {
            if (k == -1 || p[k] == p[j])
            {
                k++;
                j++;
                next[j] = k;
            }
            else
            {
                k = next[k];
                
            }
        }
    }
    
    int strStr(char *haystack, char *needle) {
        
        int sLen = (int)strlen(haystack);
        int pLen = (int)strlen(needle);
        
        if (pLen > sLen)    return -1;
        
        int *next = new int[pLen];
        getNext(needle, next);
        int i = 0;
        int j = 0;
        
        while (i < sLen && j < pLen) {
            if (j == -1 || haystack[i] == needle[j]) {
                i++;
                j++;
            }
            else {
                j = next[j];
            }
        }
        
        if (j == pLen) {
            return i - j;
        }
        else
            return -1;
        
        // my 2nd version
        //    if (!haystack || !needle)   return -1;
        //    int m = strlen(haystack);
        //    int n = strlen(needle);
        //
        //    if (m == 0 && n == 0) return 0;
        //    else if (m == 0)    return -1;
        //    else if (n == 0)    return 0;
        //    else if (m < n)     return -1;
        //
        //    int index = 0;
        //    while ((index < m) && (m-index >= n)) {
        //        if (haystack[index] == needle[0]) {
        //            int l = 1;
        //            bool found = true;
        //            while (l < n && index + l < m) {
        //                if (haystack[index+l] != needle[l]) {
        //                    found = false;
        //                    break;
        //                }
        //                ++l;
        //            }
        //            if (found)  return index;
        //        }
        //        ++index;
        //    }
        //    return -1;
        
        
        // my 1st version
        //    if (!haystack || !needle)   return -1;
        //    if (*haystack == '\0' && *needle == '\0')   return 0;
        //    else if (*haystack == '\0') return -1;
        //    else if (*needle == '\0') return 0;
        //
        //    int lh = strlen(haystack);
        //    int ln = strlen(needle);
        //    
        //    if (lh < ln)    return -1;
        //    
        //    for (int index = 0; (index < lh) && (lh-index >= ln); index++)
        //    {
        //        if (haystack[index] == needle[0])
        //        {
        //            int i = index;
        //            int j = 0;
        //            while (haystack[i] == needle[j])
        //            {
        //                if (needle[j] == '\0')
        //                    return index;
        //                else if (haystack[i] == '\0')
        //                    return -1;
        //                else
        //                {
        //                    if (needle[j+1] == '\0')
        //                        return index;
        //                    if (haystack[i+1] == '\0')
        //                        return -1;
        //                    i++;
        //                    j++;
        //                }
        //            }
        //        }
        //    }
        //    return -1;
    }
    
    string longestCommonPrefix(vector<string> &strs) {
        string ret = "";
        if (strs.size() == 0)   return ret;
        if (strs.size() == 1)   return strs[0];
        int minLen = INT_MAX;
        for (string s : strs)
            if (s.length() < minLen)
                minLen = s.length();
        
        for (int i = 0; i < minLen; i++)
        {
            for (int j = 1; j < strs.size(); j++) {
                if (strs[j][i] != strs[j-1][i])
                    return ret;
            }
            ret += strs[0][i];
        }
        
        return ret;
        
    }
    
    int titleToNumber(string s) {
        if (s.length())
        {
            int ret = 0;
            for (int i = 0; i < s.length(); i++)
            {
                ret *= 26;
                ret += s[i] - 'A' + 1;
            }
            return ret;
        }
        return 0;
    }
}