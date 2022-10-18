#include "../Server.hpp"

void Server::_kill(std::string args, User &user)
{

	std::string nickname;
	std::string reason;
	//std::vector<std::string> _args;
	Channel c;

	/*----------------command protect------------------*/
	if (!user.getIsRegistered())
		return;
	/*----------------command protect------------------*/

	if (!user.getIsOperator())
		return _errorReplies(user, ERR_NOPRIVILEGES, "KILL", "");

	try { nickname = Utils::split(args, ':').at(0); }	catch (...) { return _errorReplies(user, ERR_NEEDMOREPARAMS, "KILL", ""); }
	try { reason = Utils::split(args, ':').at(1); }		catch (...) { return _errorReplies(user, ERR_NEEDMOREPARAMS, "KILL", ""); }

	Utils::rtrim(nickname, ' ');

	std::vector<User>::iterator userToKill = findUser(nickname);
	if (userToKill == _users.end())
		return _errorReplies(user, ERR_NOSUCHNICK, "KILL", "");

	userToKill->addOutputMessage(user.getFullClientIdentifier() + " KILL");
	_sendMessageToChannels(userToKill->getChannels(), ":" + userToKill->getFullClientIdentifier() + " QUIT :killed (" + user.getFullClientIdentifier() + ") " + reason + ")");

	userToKill->addOutputMessage("ERROR :Closing Link " + _serverName + " killed (" + user.getFullClientIdentifier() + ") " + reason + ")");
	userToKill->setIsDeleted(true);
}
