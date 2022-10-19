#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <cstdlib>


class Config
{
private:
    std::map<std::string, std::string> _values;
    void readConfig();

public:
    Config();
    ~Config();
    std::string getValue(std::string key, std::string defaultValue);
};
#endif