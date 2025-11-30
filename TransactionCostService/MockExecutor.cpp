#include "MockExecutor.h"

ExecutionReport MockExecutor::execute_fill(OrderInfo& order, uint32_t& remaining) {
    ExecutionReport exec;

    exec.order_id = order.order_id;

    // Add small +/- slippage to price
    exec.price = order.expected_price + _slippage_gen(_rng);

    // Random partial fill
    uint32_t fill = std::min<uint32_t>(remaining, _fill_gen(_rng));
    exec.qty = fill;

    exec.ts = std::chrono::steady_clock::now();

    remaining -= fill;
    return exec;
}