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


	if (Server::hasUser(nickname))
	{
		user.outputBuffer += "433 *";
		user.outputBuffer += nickname;
		user.outputBuffer += " :Nickname is already in use.";
		user.outputBuffer += DELIMITER;
		return;
	}

	user.nickName = tokens[0];
}
