#include "../Server.hpp"
bool ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
		return (true);
	return (false);
}

bool invalid_nickName(std::string str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (ft_isalnum(str[i]) == 0)
			return false;
	}
	return true;
}
void Server::_nick(std::string args, User &user)
{
	Channel channel;
	std::vector<std::string> splitArgs;
	splitArgs = Utils::split(args, ' ');

	if (args.size() == 0)
	{
		_errorReplies(user, ERR_NONICKNAMEGIVEN, "NICK", channel);
		return;
	}

	std::string nickname = splitArgs[0];
	if (invalid_nickName(nickname) == false)
	{
		_errorReplies(user, ERR_ERRONEUSNICKNAME, "NICK", channel);
		return;
	}
	if (Server::hasUser(nickname, user.getNickName()))
	{
		_errorReplies(user, ERR_NICKNAMEINUSE, "NICK", channel, nickname);
		// deleteUser(user.nickName);
		return;
	}

	if (!user.getIsRegistered()) // not registered TOTO replace by !user.isRegistered
	{
		user.setNickName(nickname);
		user.addOutputMessage(": NICK :" + nickname);
	}
	else
	{
		user.addOutputMessage(":" + user.getNickName() + " NICK :" + nickname);
		user.setNickName(nickname);
		// todo envoyer le message aux autre clients (dans les memes channel)
	}
}
