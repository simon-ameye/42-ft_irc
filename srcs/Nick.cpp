#include "Nick.hpp"

Nick::Nick(std::string cmd) : Command(cmd)
{
    std::pair<std::string, std::vector<std::string> > values = parse(cmd);
    name = values.first;
    args = values.second;
}

Nick::~Nick() {}

std::pair<std::string, std::vector<std::string> > Nick::parse(std::string cmd)
{
    std::vector<std::string> parts = Utils::split(cmd, ' ');
    std::string nick = parts[1];

    std::vector<std::string> v;
    v.push_back(nick);

    std::pair<std::string, std::vector<std::string> > p(parts[0], v);
    return p;
}

void Nick::execute()
{
    if (this->getArgs()[1].size() == 0)
    {
        return;
        // return "431 :No nickname given " + DELIMITER;
    }

    // if (Server::hasUser(this->getName()))
    // {
    //     return;
    // 	//return "433 *" + nick + " :Nickname is already in use.";
    // }

    // user.nickName = nick;

    // return ":" + nick + " " + cmd;
}