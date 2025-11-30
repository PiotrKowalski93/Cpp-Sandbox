#include "MockOrderFeed.h"

using namespace std;

OrderInfo MockOrderFeed::generate_order() {
	OrderInfo ord_info;
    ord_info.order_id = _next_id++;
    ord_info.expected_price = _price_gen(_rng);
    ord_info.total_qty = _qty_gen(_rng);
    ord_info.arrival_ts = chrono::steady_clock::now();

    return ord_info;
}