#include "../Server.hpp"

void Server::_user(std::string args, User &user)
{

	Channel c;
	if (user.getIsRegistered())
		return _errorReplies(user, ERR_ALREADYREGISTRED, "USER", c);

	std::string realName;
	std::string username;
	std::string hostname;

	//example : args = "myusername myusername localhost :my real name"
	try {realName = Utils::split(args, ':').at(1);}								catch (...) {return _errorReplies(user, ERR_NEEDMOREPARAMS, "USER", c);}
	try {username = Utils::split(Utils::split(args, ':').at(0), ' ').at(0);}	catch (...) {return _errorReplies(user, ERR_NEEDMOREPARAMS, "USER", c);}
	try {hostname = Utils::split(Utils::split(args, ':').at(0), ' ').at(2);}	catch (...) {return _errorReplies(user, ERR_NEEDMOREPARAMS, "USER", c);}

	user.setUserName(username);
	user.setRealName(realName);
	user.setHostName(hostname);
	user.setIsRegistered(true);
	_commandResponces(user, RPL_WELCOME, "USER", c);
}
