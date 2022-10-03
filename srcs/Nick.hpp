#ifndef NICK_HPP
#define NICK_HPP
#include "Command.hpp"

class Nick : public Command {
private:
    std::pair<std::string, std::vector<std::string> > parse(std::string cmd);

public:
    Nick(std::string cmd);
    ~Nick();

    void execute();
};
#endif