#include "../Server.hpp"

void Server::_mode(std::string args, User &user)
{
	(void) user;
	//std::string target;
	//target = Utils::split(args, ' ')[0];
	std::cout << "------> target = " <<  args << std::endl;
	
	// std::string text;
	// text = args.substr(target.size(), args.size());
	// std::cout << "------> text = " <<  text << std::endl;
}