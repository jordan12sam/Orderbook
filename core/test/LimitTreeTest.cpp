#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <LimitTree.hpp>

namespace {
	class LimitTreeTest : public testing::Test {

	public:
		std::unique_ptr<LimitTree> buyLimitTree;
        std::unique_ptr<LimitTree> sellLimitTree;
		LimitTreeTest() {}
		virtual ~LimitTreeTest() {}
		virtual void SetUp() {
			buyLimitTree = std::make_unique<LimitTree>(Side::buy);
            sellLimitTree = std::make_unique<LimitTree>(Side::sell);
		}
	};

	TEST_F(LimitTreeTest, limitCompare)
	{
        std::shared_ptr<Limit> limit1 = std::make_shared<Limit>(1.0);
        std::shared_ptr<Limit> limit2 = std::make_shared<Limit>(3.0);

        buyLimitTree->push(limit1);
        buyLimitTree->push(limit2);

        sellLimitTree->push(limit1);
        sellLimitTree->push(limit2);

        EXPECT_DOUBLE_EQ(buyLimitTree->top()->getPrice(), limit2->getPrice());
        EXPECT_DOUBLE_EQ(sellLimitTree->top()->getPrice(), limit1->getPrice());
    }

    TEST_F(LimitTreeTest, inplaceLimitUpdate)
	{
        std::shared_ptr<Limit> limit = std::make_shared<Limit>(1.0);
        buyLimitTree->push(limit);

        EXPECT_DOUBLE_EQ(buyLimitTree->top()->getPrice(), limit->getPrice());

        std::shared_ptr<Order> order = std::make_shared<Order>();
		order->id = 1;
        limit->push_front(order);

        EXPECT_EQ(buyLimitTree->top()->front()->id, order->id);
    }

    TEST_F(LimitTreeTest, remove)
	{
        std::shared_ptr<Limit> limit1 = std::make_shared<Limit>(100);
        std::shared_ptr<Limit> limit2 = std::make_shared<Limit>(300);

        buyLimitTree->push(limit1);
        buyLimitTree->push(limit2);

        EXPECT_DOUBLE_EQ(buyLimitTree->top()->getPrice(), limit2->getPrice());

        buyLimitTree->remove(limit2);

        EXPECT_DOUBLE_EQ(buyLimitTree->top()->getPrice(), limit1->getPrice());
    }
}