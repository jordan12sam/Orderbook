#include <Configuration.hpp>

Configuration::Configuration(std::string propertySource){
    this->propertySource = propertySource;
    this->readProperties();
}

void Configuration::readProperties(){
    try{
        this->properties = toml::parse_file(this->propertySource);
        spdlog::info("Loaded property file: {}", this->propertySource);
    }
    catch (const toml::parse_error& err){
        spdlog::error("Parsing failed: {}", err.description());
    }
}