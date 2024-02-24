#pragma once

#include <iostream>
#include <fstream>
#include <map>

#include <toml++/toml.h>
#include <spdlog/spdlog.h>

class Configuration {
    public:
    toml::table properties;
    Configuration(std::string propertySource);

    private:
    std::string propertySource;
    void readProperties();
};