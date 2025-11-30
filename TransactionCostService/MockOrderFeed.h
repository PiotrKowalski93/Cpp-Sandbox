#pragma once

#include <random>
#include "TransactionCostService.h"

using namespace std;

class MockOrderFeed{
public: 
	MockOrderFeed(uint64_t start_id = 1) {
		_next_id = start_id;
		_rng = mt19937(12345);
		_price_gen = uniform_real_distribution<double>(100, 105);
		_qty_gen = uniform_int_distribution<int>(10, 100);
	}

	OrderInfo generate_order();

private: 
	uint64_t _next_id;
	mt19937 _rng;
	uniform_real_distribution<double> _price_gen;
	uniform_int_distribution<int> _qty_gen;
};

