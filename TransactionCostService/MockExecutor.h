#pragma once

#include <random>
#include "TransactionCostService.h"
using namespace std;

class MockExecutor {
public:
    MockExecutor(){
        _rng = mt19937(56789);
        _slippage_gen = uniform_real_distribution<double>(-0.05, 0.05);
        _fill_gen = uniform_int_distribution<int>(1, 10);
    }

    // Simulate 1 partial or full fill
    ExecutionReport execute_fill(OrderInfo& order, uint32_t& remaining);

private:
    mt19937 _rng;
    uniform_real_distribution<double> _slippage_gen;
    uniform_int_distribution<int> _fill_gen;
};

