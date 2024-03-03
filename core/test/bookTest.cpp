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
		std::shared_ptr<Order> order = std::make_shared<Order>();
		order->id = 1;
		order->timestamp = std::time(nullptr);
		order->side = Side::buy;
		order->price = 100;
		order->volume = 10;
		order->client = "client1";

		book->placeOrder(order);
		EXPECT_TRUE(book->orderMap.contains(1));
		EXPECT_EQ(*book->orderMap.at(1), *order);
		EXPECT_EQ(book->volumeMap.at(order->side).at(100), 10);
	}

	TEST_F(BookTest, cancelOrder)
	{
		std::shared_ptr<Order> order = std::make_shared<Order>();
		order->id = 1;
		order->timestamp = std::time(nullptr);
		order->side = Side::buy;
		order->price = 100;
		order->volume = 10;
		order->client = "client1";

		book->placeOrder(order);
		EXPECT_TRUE(book->orderMap.contains(1));
		EXPECT_EQ(*book->orderMap.at(1), *order);

		book->cancelOrder(order->id);
		EXPECT_FALSE(book->orderMap.contains(1));
		EXPECT_EQ(book->buyTree->size(), 0);
	}

	TEST_F(BookTest, matchOrders)
	{
		std::shared_ptr<Order> order1 = std::make_shared<Order>();
		order1->id = 1;
		order1->timestamp = std::time(nullptr);
		order1->side = Side::sell;
		order1->price = 100;
		order1->volume = 10;
		order1->client = "client1";

		std::shared_ptr<Order> order2 = std::make_shared<Order>();
		order2->id = 2;
		order2->timestamp = std::time(nullptr);
		order2->side = Side::buy;
		order2->price = 110;
		order2->volume = 20;
		order2->client = "client2";

		book->placeOrder(order1);
		EXPECT_TRUE(book->orderMap.contains(1));
		EXPECT_EQ(*book->orderMap.at(1), *order1);
		EXPECT_EQ(book->volumeMap.at(order1->side).at(100), 10);

		book->placeOrder(order2);
		EXPECT_FALSE(book->orderMap.contains(1));	
		EXPECT_TRUE(book->orderMap.contains(2));
		EXPECT_EQ(*book->orderMap.at(2), *order2);

	}
}