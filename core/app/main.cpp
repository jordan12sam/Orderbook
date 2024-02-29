#include <iostream>
#include <spdlog/spdlog.h>

#include <Configuration.hpp>

int main(){
	spdlog::info("Application started");
	Configuration configuration("./core/res/application.toml");
	spdlog::info(configuration.properties["spdlog"]["level"].value<std::string>().value_or("null!"));
	return 0;
}