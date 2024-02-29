#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Configuration.hpp>

class TestEnvironment : public ::testing::Environment {
 public:
  ~TestEnvironment() override {}
  virtual void SetUp() override {
    spdlog::info("Setting up test environment.");
    std::unique_ptr<Configuration> configuration = std::make_unique<Configuration>("./core/res/test.toml");

    static std::unordered_map<std::string,spdlog::level::level_enum> const logLevelTable = { 
      {"info", spdlog::level::info}, 
      {"debug", spdlog::level::debug}, 
      {"trace", spdlog::level::trace} };
    std::optional<std::string> debugLevelOptional = configuration->properties["spdlog"]["level"].value<std::string>();
    std::string debugLevelString = debugLevelOptional.has_value() && logLevelTable.contains(debugLevelOptional.value()) ? *debugLevelOptional : "info";
    spdlog::level::level_enum logLevel = logLevelTable.at(debugLevelString);
    spdlog::set_level(logLevel);
    spdlog::info("spdlog level: {} [{}].", debugLevelString, logLevel);
  }
  virtual void TearDown() override {}
};

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   ::testing::AddGlobalTestEnvironment(new TestEnvironment{});

   return RUN_ALL_TESTS();
}