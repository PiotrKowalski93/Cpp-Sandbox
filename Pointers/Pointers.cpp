// Pointers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

template <typename T>
class Auto_ptr1 {
    T* m_ptr{};

public:
    // Pass in a pointer to "own" via the constructor
    Auto_ptr1(T* ptr = nullptr)
        :m_ptr(ptr)
    {
    }

    // The destructor will make sure it gets deallocated
    ~Auto_ptr1() {
        delete m_ptr;
    }

    // Overload dereference and operator-> so we can use Auto_ptr1 like m_ptr.
    T& operator*() const { return &m_ptr; }
    T* operator->() const { return m_ptr; }
};

template <typename T>
class Auto_ptr2 {
    T* m_ptr{};

public:
    Auto_ptr2(T* ptr = nullptr)
        :m_ptr(ptr) 
    {
    }

    ~Auto_ptr2() 
    {
        delete m_ptr;
    }

    // A copy constructor that implements move semantics
    Auto_ptr2(Auto_ptr2& a)
    {
        m_ptr = a.m_ptr; // transfer our dumb pointer from the source to our local object
        a.m_ptr = nullptr; // make sure the source no longer owns the pointer
    }

    // An assignment operator that implements move semantics
    Auto_ptr2& operator=(Auto_ptr2& a)
    {
        if (&a == this)
            return *this;

        delete m_ptr; // make sure we deallocate any pointer the destination is already holding first
        m_ptr = a.m_ptr; // transfer our dumb pointer from the source to our local object
        a.m_ptr = nullptr; // make sure the source no longer owns the pointer

        return *this;
    }

    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    bool isNull() const { return m_ptr == nullptr; }
};

class Resource {
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

void useMyOwnSmartPtr() {
    Auto_ptr1<Resource> res(new Resource()); // Note the allocation of memory here
    // ... but no explicit delete needed

    // Also note that we use <Resource>, not <Resource*>
    // This is because we've defined m_ptr to have type T* (not T)
}

void passByValue(Auto_ptr1<Resource> res)
{
}

void danglingPointer() {
    Auto_ptr1<Resource> res1(new Resource());
    passByValue(res1);

    return; // After leaving passbyValue local res is destroyed, so res1 is ponting to random
}

void copyInSmartPtr() {
    Auto_ptr2<Resource> res1(new Resource());
    Auto_ptr2<Resource> res2; // Start as nullptr

    std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
    std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");

    res2 = res1; // res2 assumes ownership, res1 is set to null

    std::cout << "Ownership transferred\n";

    std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
    std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");

    return 0;
}

int main()
{
    //useMyOwnSmartPtr();
   
}

void someFunction()
{
    Resource* ptr = new Resource();

    int x;
    std::cout << "Enter an integer: ";
    std::cin >> x;

    if (x == 0)
        return; // the function returns early, and ptr won’t be deleted!

    // do stuff with ptr here

    delete ptr;
}