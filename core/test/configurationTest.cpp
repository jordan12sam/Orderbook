#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <spdlog/spdlog.h>

#include <Configuration.hpp>

namespace {
	class ConfigurationTest : public testing::Test {

	public:
		Configuration* configuration;

		ConfigurationTest() {}
		virtual ~ConfigurationTest() {}

		virtual void SetUp() {
			configuration = new Configuration("./core/res/test.toml");
		}

		virtual void TearDown() {
			delete configuration;
		}

	};

	TEST_F(ConfigurationTest, getProperty)
	{
		std::string property = configuration->properties["test"]["property"].value<std::string>().value_or("null");
		EXPECT_EQ(property, "hello world");
	}
}