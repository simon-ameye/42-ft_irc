#include "Config.hpp"

Config::Config()
{
    readConfig();
}

Config::~Config()
{
}

void Config::readConfig()
{
    std::cout << "Reading config ..." << std::endl;
    std::ifstream file("./config.ini");
    if (!file.good())
    {
        std::cout << "Unable to read config file" << std::endl;
        return;
    }
    if (file.is_open())
    {
        std::string line;
        size_t index = 0;
        while (std::getline(file, line))
        {
            if ((index = line.find("=")) == std::string::npos)
                continue;

            std::string key = line.substr(0, index);
            std::string value = line.substr(index + 1, line.size());

            _values[key] = value;
        }
        file.close();
    }
}

std::string Config::getValue(std::string key, std::string defaultValue)
{
    try
    {
        return _values.at(key);
    }
    catch(const std::out_of_range& e)
    {
        return defaultValue;
    }    
}