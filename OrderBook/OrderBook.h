#pragma once

#include <iostream>

enum class Side { Bid, Ask };

struct OrderId {
	uint64_t value;
};

struct Volume {
	uint64_t value;
};

struct Price {
	uint64_t value;
};

class OrderBook
{
	void AddOrder(OrderId orderId, Side side, Price price, Volume volume);
	void Modify(OrderId orderId, Volume newVolume);
	void DeleteOrder(OrderId orderId);
};

