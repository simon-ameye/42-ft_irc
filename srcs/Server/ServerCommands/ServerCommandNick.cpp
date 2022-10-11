#include "../Server.hpp"
bool	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
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
	if (Server::hasUser(nickname, user.nickName))
	{
		_errorReplies(user, ERR_NICKNAMEINUSE, "NICK", channel, nickname);
		//deleteUser(user.nickName);
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

		user._outputMessage += ":";
		user._outputMessage += user.nickName;
		user._outputMessage += " NICK :";
		user._outputMessage += nickname;
		user._outputMessage += DELIMITER;
		user.nickName = nickname;

		// todo envoyer le message aux autre clients (dans les memes channel)
	}
}
