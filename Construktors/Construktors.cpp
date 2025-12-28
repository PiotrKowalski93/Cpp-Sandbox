#include <iostream>
using namespace std;

// good rule of thumb: An object is cheap to copy if it uses 
// 2 or fewer “words” of memory (where a “word” is approximated by the size of a memory address) 
// and it has no setup costs.
#define isSmall(T) (sizeof(T) <= 2 * sizeof(void*))

struct S
{
    double a;
    double b;
    double c;
};

int main()
{
    std::cout << std::boolalpha; // print true or false rather than 1 or 0
    std::cout << isSmall(int) << '\n'; // true

    double d{};
    std::cout << isSmall(d) << '\n'; // true
    std::cout << isSmall(S) << '\n'; // false

    int x{ 5 };
    int* y;
    y = &x;
    cout << *y << endl;
    cout << x << endl;
    cout << &x << endl;
    cout << *&x << endl;


    return 0;
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
