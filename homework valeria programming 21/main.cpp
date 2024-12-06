//
//  main.cpp
//  homework valeria programming 21
//
//  Created by Valeria  Bukova on 07.12.2024.
//



#include <iostream>
using namespace std;


template <typename T>
class MyUniquePtr
{
private:
    T* ptr;

public:
    explicit MyUniquePtr(T* p = nullptr) : ptr(p) {}

    ~MyUniquePtr() {
        delete ptr;
    }

    MyUniquePtr(MyUniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    MyUniquePtr& operator=(MyUniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

   
    T* get() const {
        return ptr;
    }

   
    T& operator*() const {
        return *ptr;
    }
 
    T* operator->() const {
        return ptr;
    }

    
    MyUniquePtr(const MyUniquePtr&) = delete;
    MyUniquePtr& operator=(const MyUniquePtr&) = delete;
};

template <typename T>
class MySharedPtr {
private:
    T* ptr;
    unsigned* count;
public:
    explicit MySharedPtr(T* p = nullptr) : ptr(p), count(new unsigned(1)) {}

    ~MySharedPtr() {
        if (--(*count) == 0) {
            delete ptr;
            delete count;
        }
    }

    MySharedPtr(const MySharedPtr& other) : ptr(other.ptr), count(other.count) {
        ++(*count);
    }

    MySharedPtr& operator=(const MySharedPtr& other) {
        if (this != &other) {
            if (--(*count) == 0) {
                delete ptr;
                delete count;
            }
            ptr = other.ptr;
            count = other.count;
            ++(*count);
        }
        return *this;
    }

   
    T* get() const {
        return ptr;
    }

   
    T& operator*() const {
        return *ptr;
    }

    
    T* operator->() const {
        return ptr;
    }
};


class Test
{
public:
    void display()
    {
        cout << "Test object function called" << endl;
    }
};

int main() {

    {
        MyUniquePtr<Test> uniquePtr1(new Test());
        uniquePtr1->display();

        
        MyUniquePtr<Test> uniquePtr2 = move(uniquePtr1);
        uniquePtr2->display();

       
    }

    {
        MySharedPtr<Test> sharedPtr1(new Test());
        sharedPtr1->display();

        {
            MySharedPtr<Test> sharedPtr2 = sharedPtr1;
            sharedPtr2->display();
        }

        
    }

    return 0;
}
