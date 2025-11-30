#include <iostream>
#include <thread>
#include "TransactionCostService.h"
#include "MockOrderFeed.h"
#include "MockExecutor.h"

using namespace std;

int main()
{
    TransactionCostService tcs;
    MockOrderFeed feed;
    MockExecutor executor;

    // Generate 5 orders
    for (int i = 0; i < 5; ++i) {
        OrderInfo order = feed.generate_order();
        tcs.on_new_order(order);

        uint32_t remaining = order.total_qty;

        // Simulate exchange executions
        while (remaining > 0) {
            ExecutionReport exec = executor.execute_fill(order, remaining);
            tcs.on_execution(exec);

            this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        auto stats = tcs.get_stats(order.order_id);

        cout << "Order " << order.order_id << ":\n";
        cout << "- VWAP: " << stats.vwap << "\n";
        cout << "- Filled: " << stats.filled << "/" << order.total_qty << "\n";
        cout << "- Slippage: " << stats.slippage << "\n\n";
    }
}