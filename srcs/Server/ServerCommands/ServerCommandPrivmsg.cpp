#include "../Server.hpp"

void Server::_privmsg(std::string args, User &user)
{
	(void) user;
	std::string target;
	target = Utils::split(args, ' ')[0];
	std::cout << "------> target = " <<  target << std::endl;
	
	std::string text;
	text = args.substr(target.size(), args.size());
	std::cout << "------> text = " <<  text << std::endl;

//no need add error cause fin alone if not enought param
	
}
