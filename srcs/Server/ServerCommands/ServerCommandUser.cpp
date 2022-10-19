#include "../Server.hpp"

void Server::_user(std::string args, User &user)
{
	/*----------------command protect------------------*/
	if (!user.getIsPassProvided())
		return;
	/*----------------command protect------------------*/

	if (user.getIsRegistered())
		return _errorReplies(user, ERR_ALREADYREGISTRED, "USER", "");

	std::string realname;
	std::string username;
	std::string hostname;

	//example : args = "myusername myusername localhost :my real name"
	try {realname = Utils::split(args, ':').at(1);}								catch (...) {return _errorReplies(user, ERR_NEEDMOREPARAMS, "USER", "");}
	try {username = Utils::split(Utils::split(args, ':').at(0), ' ').at(0);}	catch (...) {return _errorReplies(user, ERR_NEEDMOREPARAMS, "USER", "");}
	try {hostname = Utils::split(Utils::split(args, ':').at(0), ' ').at(2);}	catch (...) {return _errorReplies(user, ERR_NEEDMOREPARAMS, "USER", "");}

	user.setUserName(username);
	user.setRealName(realname);
	//user.setHostName(hostname);

	getpeername(user.getFd(), (struct sockaddr *)&_sin, (socklen_t *)&_sizeofsin);
	user.setHostName(inet_ntoa(_sin.sin_addr));
}
