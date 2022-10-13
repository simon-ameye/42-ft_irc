#include "../Server.hpp"
static bool isValidChar(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') //Nick "*" MUST be denied because it is the default nick
		return (true);
	return (false);
}

static bool isInvalidNick(std::string str)
{
	if (str.size() == 0)
		return true;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (isValidChar(str[i]) == 0)
			return true;
	}
	return false;
}

void Server::_nick(std::string args, User &user)
{
	/*----------------command protect------------------*/
	if (!user.getIsPassProvided())
		return;
	/*----------------command protect------------------*/

	//std::vector<std::string> splitArgs = Utils::split(args, ' ');
	//if (args.size() == 0)
	//{
	//	_errorReplies(user, ERR_NONICKNAMEGIVEN, "NICK", "");
	//	return;
	//}
	//std::string nickname = splitArgs[0];

	std::string nickname;
	try
	{
		nickname = Utils::split(args, ' ').at(0);
	}
	catch (...)
	{
		return _errorReplies(user, ERR_NONICKNAMEGIVEN, "NICK", "");
	}

	if (isInvalidNick(nickname))
	{
		_errorReplies(user, ERR_ERRONEUSNICKNAME, "NICK", "");
		return;
	}

	if (Server::hasUser(nickname, user.getNickName()))
	{
		std::string message = ": 433 ";
		message += user.getNickNameOrStar();
		message += " ";
		message += nickname;
		message += " :Nickname is already in use";
		user.addOutputMessage(message);
		return;
	}

	//user.addOutputMessage(":" + user.getFullClientIdentifier() + " NICK " + nickname);
	user.setNickName(nickname);
	user.addOutputMessage(": NICK :" + nickname);

	//if (!user.getIsRegistered()) // not registered TOTO replace by !user.isRegistered
	//{
	//	user.setNickName(nickname);
	//	user.addOutputMessage(": NICK " + nickname);
	//}
	//else
	//{
	//	user.addOutputMessage(":" + user.getNickName() + " NICK :" + nickname);
	//	user.setNickName(nickname);
	//	// todo envoyer le message aux autre clients (dans les memes channel)
	//}
}
