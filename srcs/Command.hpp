#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <vector>
#include "Utils.hpp"

class Command
{
protected:
    std::string name;
    std::vector<std::string> args;
    std::string command;

protected:
    virtual std::pair<std::string, std::vector<std::string> > parse(std::string cmd) = 0;

public:
    std::string getName();
    std::vector<std::string> getArgs();
    Command(std::string cmd);
    ~Command();

    virtual void execute() = 0;
};

#endif
