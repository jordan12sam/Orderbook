#include <iostream>
#include <spdlog/spdlog.h>

#include <Configuration.hpp>
#include <Book.hpp>
#include <Order.hpp>

std::vector<std::string> getNextLineAndSplitIntoTokens(std::istream& str)
{
    std::vector<std::string> result;
    std::string line;
    std::getline(str,line);

    std::stringstream lineStream(line);
    std::string cell;

    while(std::getline(lineStream,cell, ','))
    {
        result.push_back(cell);
    }
    if (!lineStream && cell.empty())
    {
        result.push_back("");
    }
    return result;
}

int main(){
	spdlog::info("Application started");

	Configuration configuration("./core/res/application.toml");
	spdlog::set_level(spdlog::level::info);

	spdlog::info("Loading input data");
	std::filebuf fb;
	if (fb.open ("./core/res/AMZN.csv",std::ios::in))
	{
		Book orderbook;
		spdlog::info("Streaming orders...");
		std::istream is(&fb);
		while (is) {
			std::vector<std::string> result = getNextLineAndSplitIntoTokens(is);
			if (result.size() == 6) {

				bool bside;
				if (result[4] == "True") {
					bside = Side::buy;
				}
				else if (result[4] == "False") {
					bside = Side::sell;
				}
				spdlog::trace("Assigned side");

				std::shared_ptr<Order> order = std::make_shared<Order>(std::stoull(result[1]), bside, std::stoull(result[3]), std::stoull(result[2]), result[5]);
				spdlog::info("Order: [id={}, side={}, price={}, volume={}, client={}]",
				order->id, order->side, order->price, order->volume, order->client);
				if (result[0] == "1") {
					spdlog::trace("Placing Order...");
					orderbook.placeOrder(order);
				}
				else if (result[0] == "3") {
					spdlog::trace("Cancel Order...");
					orderbook.cancelOrder(order->id);
				}
			}
		}
		fb.close();

		if (!orderbook.sellTree->empty()) {
			spdlog::info("Best ask: {}, levels={}", orderbook.sellTree->top()->getPrice(),  orderbook.sellTree->size());
		} else {
			spdlog::info("No asks.");
		}
		if (!orderbook.buyTree->empty()) {
			spdlog::info("Best bid: {}, levels={}", orderbook.buyTree->top()->getPrice(), orderbook.buyTree->size());
		} else {
			spdlog::info("No bids.");
		}
	}
	return 0;
}