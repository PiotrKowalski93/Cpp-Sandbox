#include <iostream>
using namespace std;

int main()
{
    int x{ 1 };
    int& ref{ x };

    std::cout << x << ref << '\n';

    int y{ 2 };
    ref = y;
    y = 3;

    std::cout << x << " " << ref << " " << y << '\n';

    x = 4;

    std::cout << x << ref << '\n';
}

class Sample {
private:
    int* ptr;

public:
    // Constructor
    Sample(int value) {
        ptr = new int(value);
        cout << "Constructor called\n";
    }

    // Copy Constructor
    Sample(Sample& x) {
        ptr = x.ptr;
        cout << "Copy constructor called\n";
    }

    // Move Construktor
    Sample(Sample&& x) noexcept
        : ptr(x.ptr) 
    {
        x.ptr = nullptr;
    }

    // Destructor
    ~Sample() {

    }

};
