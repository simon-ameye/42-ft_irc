#include "../Server.hpp"

void			Server::_oper(std::string args, User &user)
{
	std::vector<std::string> splitArgs;
	splitArgs = Utils::split(args, ' ');

	Channel channel;
	std::string name;
	std::string pass;
	std::string opername;
	std::string operpass;

	opername = OPERNAME;
	operpass = OPERPASS;

	//ERR_NOOPERHOST : not required
	if (splitArgs.size() < 2)
	{
		_errorReplies(user, ERR_NEEDMOREPARAMS, "OPER", channel);
		return;
	}

	name = splitArgs[0];
	pass = splitArgs[1];

	if (name != opername || pass != operpass)
	{
		_errorReplies(user, ERR_PASSWDMISMATCH, "OPER", channel);
		return;
	}

	user._operator = 1;
	_commandResponces(user, RPL_YOUREOPER, "OPER", channel);

}
