// Runetime polimorphism and composition

#include <iostream>
#include <vector>

struct Order {
    int id;
    double price;
};

class InheritanceOrderBook : public std::vector<Order>
{

};

class CompositionOrderBook {
    std::vector<Order> _orders;
public:

    // const - does not modify object, can be used on const objects
    // noexcept - does not throws exception, can be optimised by compiler
    auto size() const noexcept {
        return _orders.size();
    }
};

// Runetime polymorphism using virtual functions
class RunetimeExample {
public:
    virtual void placeOrder() {
        printf("RunetimeExample::placeOrer()\n");
    }
};

class SpecificRunetimeExample : public RunetimeExample {
public:
    void placeOrder() override {
        printf("SpecificRunetimeExample::placeOrer()\n");
    }
};

// Compile-time polymorphism using the CRTP
template <typename type>
class CRTPExample
{
public:
    void placeOrder() {
        static_cast<type*>(this)->actual_placeOrder();
    }

    void actual_placeOrder() {
        printf("CRTPExample::actual_placeOrder()\n");
    }
};

class SpecificCRTPExample : public CRTPExample<SpecificCRTPExample> {
public:
    void actual_placeOrder() {
        printf("SpecificCRTPExample::actual_placeOrder()\n");
    }
};

int main()
{
    InheritanceOrderBook _i;
    CompositionOrderBook _c;

    printf("InheritanceOrderBook::size():%lu CompositionOrderBook:%lu\n", _i.size(), _c.size());
    printf("\n");
    printf("\n");

    RunetimeExample* _runetime = new SpecificRunetimeExample();
    _runetime->placeOrder();

    CRTPExample<SpecificCRTPExample> _crtp;
    _crtp.placeOrder();
    _crtp.actual_placeOrder();
}
