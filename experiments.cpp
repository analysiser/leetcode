//
//  experiments.cpp
//  Leetcode
//
//  Created by Xiao Li on 2/18/15.
//  Copyright (c) 2015 Xiao. All rights reserved.
//

#include "experiments.h"

namespace _exp {
    
    ///// operator overload experiements
    class MyInt {
    public:
        MyInt() { v = 0; }
        MyInt& operator++();    // prefix increment: increment and fetch
        MyInt& operator--();    // prefix decrement: decrement and fetch
        
        const MyInt operator++(int);    // postfix increment: fetch and increment
        const MyInt operator--(int);    // postfix decrement: fetch and decrement
        
        void* operator new(size_t size, int uselessArg) {
            void *raw = malloc(sizeof(MyInt));
            return raw;
        }
        int v;
    };
    
    MyInt& MyInt::operator++() {
        v += 1; // *this += 1;
        return *this;
    }
    
    const MyInt MyInt::operator++(int) {
        const MyInt oldValue = *this;
        v += 1; // ++(*this);
        return oldValue;
    }
    
    
    //// placement new
    class Widget {
    public:
        Widget(int size) {
            cout<<"I am a constructor, I don't like new operator"<<endl;
        }
        
        ~Widget() {
            cout<<"I am a destructor, cya"<<endl;
        }
        
        void printSomething() {
            cout<<"I printed something"<<endl;
        }
        
        // Placement new
        void* operator new(size_t, void *location) {
            return location;
        }
    };

    // buffer for placement new allocation, widgetSize for constructor
    Widget *initializeWidget(void *buffer, int widgetSize) {
        return new (buffer) Widget(widgetSize);
    }
    
    
    //// auto_ptr
    class DataProcessor{
    public:
        DataProcessor() { }
        ~DataProcessor() { }
        void doProcess() {
            
            int test = rand() % 5;
            cout << "value = "<< test << endl;

            bool sometingWrong = (test == 0);
            if (sometingWrong) {
                throw (1 == 0);
            }
        }
    };
    
    template <class T>
    class AutoPtr {
    public:
        AutoPtr(T * p = 0) : ptr(p) { }
        ~AutoPtr() { delete ptr; }
        T* operator->() {
            return ptr;
        }
        
        T *ptr;
        
    };

    // preprocessing, returns a pointer
    DataProcessor *readData(int dataSource) {
        return new DataProcessor();
    }

    void processData(int dataSource) {
        cout<<"data is being processed"<<endl;
        
        if (dataSource) {
            AutoPtr<DataProcessor> ds(readData(dataSource));
            try {
                ds->doProcess();
            } catch (...) {
                cerr<<"I caught an exception LOL"<<endl;
            }
        }
    }
    
    
    // parse and simplify math expression
    
#define SMS_1   "1"
#define SMS_2   "ABC2"
#define SMS_3   "DEF3"
#define SMS_4   "GHI4"
#define SMS_5   "JKL5"
#define SMS_6   "MON6"
#define SMS_7   "PQRS7"
#define SMS_8   "TUV8"
#define SMS_9   "WXYZ9"
#define SMS_ASTER   " *"
#define SMS_BREAK   ".#"

    void initializeLUT(unordered_map<char, string> &lut, unordered_set<char> &chars) {
        lut.insert(make_pair('1', SMS_1));
        lut.insert(make_pair('2', SMS_2));
        lut.insert(make_pair('3', SMS_3));
        lut.insert(make_pair('4', SMS_4));
        lut.insert(make_pair('5', SMS_5));
        lut.insert(make_pair('6', SMS_6));
        lut.insert(make_pair('7', SMS_7));
        lut.insert(make_pair('8', SMS_8));
        lut.insert(make_pair('9', SMS_9));
        lut.insert(make_pair('*', SMS_ASTER));
        lut.insert(make_pair('#', SMS_BREAK));
        
        chars = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '*', '#'};
    }
    
    bool isLegal(char c, unordered_set<char> &chars) {
        return (chars.find(c) != chars.end());
    }
    
    // Epic online test programming : SMS parsing
    string parseMessage(const string input) {
        
        if (input.size() == 0) {
            return "";
        }
        
        unordered_map<char, string> lut;
        unordered_set<char> legals;
        
        initializeLUT(lut, legals);
        
        string ret = "";
        for (int i = 0; i < input.size();) {
            char c = input[i];
            if (!isLegal(c, legals)) {
                std::cerr << "Illegal character: " << c << std::endl;
                i++;
            }
            else {
                auto it = lut.find(c);
                string table = it->second;
                
                int j = 0;
                while ((i + j) < input.size() && input[i + j] == input[i]) {
                    j++;
                }
                
                if (c == '1') {
                    for (int k = 0; k < j; k++) {
                        ret += '1';
                    }
                }
                else {
                    int index = (j - 1) % table.size();
                    char next = table[index];
                    if (next != '.') {
                        ret += next;
                    }
                }
                
                i += j;
            }
        }
        
        cout<<input<<" "<<ret<<endl;
        return ret;
    }
    
    
    int64_t getWeightedAvg(const vector<int> input) {
        if (input.size() < 4) {
            return 0;
        }
        int maxLUT[3] = {INT_MIN, INT_MIN, INT_MIN};
        int64_t sum = 0;
        for (int i = 0; i < input.size(); i++) {
            int v = input[i];
            sum += static_cast<int64_t>(v);
            if ((v != static_cast<int64_t>(INT_MIN)) && (v > maxLUT[0])) {
                if (v > maxLUT[2]) {
                    maxLUT[0] = maxLUT[1];
                    maxLUT[1] = maxLUT[2];
                    maxLUT[2] = v;
                }
                else if (v > maxLUT[1]) {
                    maxLUT[0] = maxLUT[1];
                    maxLUT[1] = v;
                }
                else {
                    maxLUT[0] = v;
                }
            }
        }
        
        for (int i = 0; i < 3; i++) {
            sum -= static_cast<int64_t>(maxLUT[i]);
        }
        
        sum /= (input.size() - 3);
        return sum;
    }
    
    
    void movePtr(char *p) {
        p++;
        p++;
        p++;
    }
    
    bool isOverlap(pair<int, int> &a, pair<int, int> b) {
        return !((a.second < b.first) || (a.first > b.second));
    }
    
    pair<int, int> mergeRange(pair<int, int> &a, pair<int, int> b) {
        return make_pair(min(a.first, b.first), max(a.second, b.second));
    }
    
    
    // given ranges: [1, 3], [10, 100], [7, 9], [11, 12], [2, 4], each manifest a range
    // find the unique range that doesn't overlapping with others
    pair<int, int> getUniqueRange(vector<pair<int, int> > ranges) {
        
        vector<pair<int, int> > next;
        
        while (ranges.size() > 1) {
            
            pair<int, int> current = ranges.front();
            bool overlapped = false;
            
            for (auto it = ranges.begin() + 1; it != ranges.end(); it++) {
                
                if (isOverlap(current, *it)) {
                    current = mergeRange(current, *it);
                    overlapped = true;
                }
                else {
                    next.push_back(*it);
                }
            }
            
            if (!overlapped) {
                return current;
            }
            
            
            ranges = next;
            next.clear();
        }
        
        return ranges[0];
    }
    
    
    // experiment functions entrance
    void expMain() {
        
        MyInt i;
        MyInt prefix = i++;
        cout<<"Prefix = "<<prefix.v<<endl;
        
        MyInt postfix = ++i;
        cout<<"Postfix = "<<postfix.v<<endl;
        
        void *buffer = operator new (sizeof(Widget));
        Widget *myWidget = initializeWidget(buffer, 10);

        myWidget->printSomething();

        myWidget->~Widget();

        operator delete (buffer);
        
        cout<<"========================="<<endl;
        for (int i = 9; i >= 0; i--) {
            processData(i);
        }
        cout<<"========================="<<endl;
        
        parseMessage("22");
        parseMessage("23");
        parseMessage("223");
        parseMessage("22#2");
        parseMessage("3#33");
        parseMessage("2222");
        parseMessage("2222#2");
        parseMessage("22222");
        parseMessage("222222");
        parseMessage("#33#44#");
        parseMessage("#44#444");
        parseMessage("#4*222#");
        parseMessage("33*222*4");
        parseMessage("1111111");
        parseMessage("22**#*#*#**#**11");
        
        
        char a[] = "abcdefg";
        movePtr(a);
        cout<<*a<<endl;
        
//        pair<int, int> 
        
        vector<pair<int, int> > testcase = {{7, 9}, {1, 3}, {10, 100}, {11, 12}, {2, 4}};
        auto res = getUniqueRange(testcase);
        cout<<res.first<<" "<<res.second<<endl;
        
    }
}