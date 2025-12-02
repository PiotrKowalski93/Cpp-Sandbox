#include "OrderBook.h"
#include <map>
#include <vector>

class OrderBook {
	// --------- vector ---------
	std::vector<std::pair<Price, Volume>> vBidLevels;
	std::vector<std::pair<Price, Volume>> vAskLevels;

	void AddOrder(Side side, Price price, Volume volume) {
		if (side == Side::Bid)
			return AddOrder(vBidLevels, price, volume, std::greater<Price>());
		else
			return AddOrder(vAskLevels, price, volume, std::less<Price>());
	}

	template <class T, class Compare>
	void AddOrder(T& levels, Price price, Volume volume, Compare comp) {
		auto it = std::lower_bound(levels.begin(), levels.end(), price,
			[comp](const auto& p, Price price) { return comp(p.first, price); }); // WTF IS THAT?! TODO: understand

		if (it != levels.end() && it->first == price)
			it->second += volume;
		else
			levels.insert(it, { price, volume });
	}

	auto GetBestPricesVector() {
		//TODO: How to return form it
		//return { vBidLevels.front().first, vAskLevels.front().first };
	}

	// --------- reversed vector ---------
	std::vector<std::pair<Price, Volume>> rvBidLevels;
	std::vector<std::pair<Price, Volume>> rvAskLevels;

	void AddOrderReversed(Side side, Price price, Volume volume) {
		if (side == Side::Bid)
			return AddOrder(rvBidLevels, price, volume, std::less<Price>());
		else
			return AddOrder(rvAskLevels, price, volume, std::greater<Price>());
	}

	auto GetBestPricesReversedVector() {
		//TODO: How to return form it
		//return { rvBidLevels.rbegin()->first, rvAskLevels.rbegin()->first };
	}

	// --------- map ---------
	std::map<Price, Volume, std::greater<Price>> mBidLevels;
	std::map<Price, Volume, std::less<Price>> mAskLevels;

	template <class T>
	typename T::iterator AddOrder(T& levels, Price price, Volume volume) {
		auto [it, inserted] = levels.try_emplace(price, volume);
		if (inserted == false) {
			it->second += volume;
		}
		return it;
	}

	template <class T>
	void DeleteOrder(typename T::iterator it, T& levels, Price price, Volume volume) {
		it->second -= volume;
		if (it->second <= 0) {
			levels.erase(it);
		}
	}
};

// TODO: Add concept to the methods as constraint
//template <typename T> concept MapLike = requires(T t, Price p, Volume v) {
//	{ 
//		t.try_emplace(p, v) 
//	} 
//	-> std::same_as<std::pair<typename T::iterator, bool>>;
//	{ 
//		t.begin() 
//	} 
//	-> std::same_as<typename T::iterator>;
//};