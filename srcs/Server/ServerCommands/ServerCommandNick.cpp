#include "../Server.hpp"

void Server::_nick(std::vector<std::string> tokens, User &user)
{
	if (tokens.size() == 0)
	{
		user.outputBuffer += "431 :No nickname given ";
		user.outputBuffer += DELIMITER;
		return;
	}

	std::string nickname = tokens[0];

	if (Server::hasUser(nickname, user.nickName))
	{
		user.outputBuffer += "433 *";
		user.outputBuffer += nickname;
		user.outputBuffer += " :Nickname is already in use.";
		user.outputBuffer += DELIMITER;
		return;
	}

	if (user.nickName.size() == 0) // not registered TOTO replace by !user.isRegistered
	{
		user.nickName = nickname;
		user.outputBuffer += ": NICK";
		user.outputBuffer += " :" + nickname;
		user.outputBuffer += DELIMITER;
	}
	else
	{
		//:user42!user42@localhost NICK :fffff
		user.outputBuffer += ":";
		user.outputBuffer += user.nickName;
		user.outputBuffer += "@"+user.hostName;
		user.outputBuffer += " NICK ";
		user.outputBuffer += ":";
		user.outputBuffer += nickname;
		user.outputBuffer += DELIMITER;
		user.nickName = nickname;
	}
}
