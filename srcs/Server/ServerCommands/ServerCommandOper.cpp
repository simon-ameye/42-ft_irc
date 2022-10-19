#include "../Server.hpp"

// ERR_NOOPERHOST not supported

void Server::_oper(std::string args, User &user)
{
	/*----------------command protect------------------*/
	if (!user.getIsRegistered())
		return;
	/*----------------command protect------------------*/

	std::vector<std::string> splitArgs = Utils::split(args, ' ');

	if (splitArgs.size() < 2)
		return _errorReplies(user, ERR_NEEDMOREPARAMS, "OPER", "");

	std::string name = splitArgs[0];
	std::string pass = splitArgs[1];

	std::string opername = getConfig().getValue("opername", "opername");
	std::string operpass = getConfig().getValue("operpass", "operpass");

	if (name != opername || pass != operpass)
		return _errorReplies(user, ERR_PASSWDMISMATCH, "OPER", "");

	user.setIsOperator(true);
	_commandResponces(user, RPL_YOUREOPER, "OPER", "");
}
