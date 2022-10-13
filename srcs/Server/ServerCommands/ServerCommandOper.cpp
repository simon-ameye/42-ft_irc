#include "../Server.hpp"

void			Server::_oper(std::string args, User &user)
{
	/*----------------command protect------------------*/
	if (!user.getIsPassProvided())
		return;
	if (user.getNickName() == "*")
		return;
	/*----------------command protect------------------*/

	std::vector<std::string> splitArgs;
	splitArgs = Utils::split(args, ' ');

	std::string name;
	std::string pass;
	std::string opername;
	std::string operpass;

	opername = OPERNAME;
	operpass = OPERPASS;

	//ERR_NOOPERHOST : not required
	if (splitArgs.size() < 2)
	{
		_errorReplies(user, ERR_NEEDMOREPARAMS, "OPER", "");
		return;
	}

	name = splitArgs[0];
	pass = splitArgs[1];

	if (name != opername || pass != operpass)
	{
		_errorReplies(user, ERR_PASSWDMISMATCH, "OPER", "");
		return;
	}

	user.setIsOperator(true);
	_commandResponces(user, RPL_YOUREOPER, "OPER", "");

}
