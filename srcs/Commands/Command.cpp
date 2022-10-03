
#include "Command.hpp"

Command::Command(std::string cmd)
{
    cmd = cmd;
    std::pair<std::string, std::vector<std::string>> values = parse(cmd);
    name = values.first;
    args = values.second;
}

Command::~Command() {}

std::vector<std::string> Command::getArgs()
{
    return args;
}

std::string Command::getName()
{
    return name;
}