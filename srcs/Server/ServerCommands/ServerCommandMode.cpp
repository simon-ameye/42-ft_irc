#include "../Server.hpp"

void Server::_mode(std::string args, User &user)
{
	(void) user;

    std::string nickname;
	nickname = Utils::split(args, ' ')[0];
	std::cout << "------> nickname = " <<  nickname << std::endl;
	
	std::string param;
	param = args.substr(nickname.size(), args.size());
	std::cout << "------> param = " <<  param << std::endl;

    if (param.compare("+i"))
	    std::cout << "------ INVITE ------" << std::endl;
}