#pragma once

#include <cstdint>
#include <chrono>
#include <unordered_map>

using namespace std;

struct OrderInfo {
	uint64_t order_id;
	double expected_price;
	uint32_t total_qty;
	chrono::steady_clock::time_point arrival_ts;
};

struct ExecutionReport {
	uint64_t order_id;
	double price;
	uint32_t qty;
	chrono::steady_clock::time_point ts;
};

struct OrderStats{
	double sum_px_qty;
	uint32_t filled = 0;
	double slippage = 0.0;
	double vwap = 0.0;
};

class TransactionCostService {
public:
	TransactionCostService() {
		_orders.reserve(100.000);
		_stats.reserve(100.000);
	}

	void on_new_order(OrderInfo& info);
	void on_execution(ExecutionReport& exec);
	OrderStats get_stats(uint64_t order_id);

private:
	unordered_map<uint64_t, OrderInfo> _orders;
	unordered_map < uint64_t, OrderStats> _stats;
};


