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

        
        
    }
}