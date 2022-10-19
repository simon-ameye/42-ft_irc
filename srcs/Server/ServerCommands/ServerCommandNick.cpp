#include "../Server.hpp"
static bool isValidChar(int c)
{
    // nickname "*" must be denied because it is the default nick
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')
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

	std::string nickname;
	try { nickname = Utils::split(args, ' ').at(0); }
	catch (...) { return _errorReplies(user, ERR_NONICKNAMEGIVEN, "NICK", ""); }

	if (isInvalidNick(nickname))
		return _errorReplies(user, ERR_ERRONEUSNICKNAME, "NICK", "");

    // we don't do `_errorReplies(user, ERR_NICKNAMEINUSE, "NICK", "")` since
    // irssi ask for a particular string format here (error code before servername)
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

    // no need to send different message if registered
	user.addOutputMessage(":" + user.getFullClientIdentifier() + " NICK " + nickname);
	user.setNickName(nickname);
}
