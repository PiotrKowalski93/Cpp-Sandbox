#include "TransactionCostService.h"

void TransactionCostService::on_new_order(OrderInfo &info) {
	_orders[info.order_id] = info;
	_stats[info.order_id] = OrderStats{};
}

OrderStats TransactionCostService::get_stats(uint64_t order_id) {
	auto order_it = _stats.find(order_id);
	if (order_it == _stats.end()) return OrderStats{};
	return order_it->second;
}

void TransactionCostService::on_execution(ExecutionReport& report) {
	auto order_it = _orders.find(report.order_id);
	if (order_it == _orders.end()) return;

	auto& order = order_it->second;
	auto& stats = _stats[report.order_id]; // if exists -> gets, otherwise creates

	// Updae VMAP Calculation
	stats.sum_px_qty += report.price * report.qty;
	stats.filled += report.qty;
	stats.vwap = stats.sum_px_qty / stats.filled;

	// Slippage vs expected price
	stats.slippage = (stats.vwap - order.expected_price) * stats.filled;
}
