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
}