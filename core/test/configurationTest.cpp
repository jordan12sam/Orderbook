#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Configuration.hpp>

namespace {
	class ConfigurationTest : public testing::Test {

	public:
		std::unique_ptr<Configuration> configuration;
		ConfigurationTest() {}
		virtual ~ConfigurationTest() {}
		virtual void SetUp() {
			configuration = std::make_unique<Configuration>("./core/res/test.toml");
		}
	};

	TEST_F(ConfigurationTest, getProperty)
	{
		std::string property = configuration->properties["test"]["property"].value<std::string>().value_or("null");
		EXPECT_EQ(property, "hello world");
	}
}