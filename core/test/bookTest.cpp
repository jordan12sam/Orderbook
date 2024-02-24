#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Book.hpp>

namespace {
	class BookTest : public testing::Test {

	public:
		std::unique_ptr<Book> book;
		BookTest() {}
		virtual ~BookTest() {}
		virtual void SetUp() {
			book = std::make_unique<Book>();
		}
	};

	TEST_F(BookTest, placeOrder)
	{
		Order order;
		order.id = 1;
		order.timestamp = std::time(nullptr);
		order.side = buy;
		order.price = 0.123456;
		order.volume = 10;
		order.client = "client1";

		book->placeOrder(order);
		EXPECT_TRUE(book->orderMap.contains(1));
		EXPECT_EQ(book->orderMap.at(1), order);
	}
}