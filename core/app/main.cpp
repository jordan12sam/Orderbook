#include <iostream>
#include <spdlog/spdlog.h>

#include <Configuration.hpp>

int main(){
	spdlog::info("Application started");
	Configuration configuration("./core/res/application.toml");
	spdlog::info(configuration.properties["server"]["port"].value<int>().value_or(0000));
	return 0;
}