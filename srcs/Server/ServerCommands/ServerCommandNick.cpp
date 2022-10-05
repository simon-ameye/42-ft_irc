#include "../Server.hpp"

void Server::_nick(std::string args, User &user)
{
	std::vector<std::string> splitArgs;
	splitArgs = Utils::split(args, ' ');

	if (args.size() == 0)
	{
		user._outputMessage += "431 :No nickname given ";
		user._outputMessage += DELIMITER;
		return;
	}

	std::string nickname = splitArgs[0];

	if (Server::hasUser(nickname, user.nickName))
	{
		user._outputMessage += "433 *";
		user._outputMessage += nickname;
		user._outputMessage += " :Nickname is already in use.";
		user._outputMessage += DELIMITER;
		return;
	}

	if (user.nickName.size() == 0) // not registered TOTO replace by !user.isRegistered
	{
		user.nickName = nickname;
		user._outputMessage += ": NICK";
		user._outputMessage += " :" + nickname;
		user._outputMessage += DELIMITER;
	}
	else
	{
		//:user42!user42@localhost NICK :fffff
		user._outputMessage += ":";
		user._outputMessage += user.nickName;
		user._outputMessage += "@"+user.hostName;
		user._outputMessage += " NICK ";
		user._outputMessage += ":";
		user._outputMessage += nickname;
		user._outputMessage += DELIMITER;
		user.nickName = nickname;
	}
}
