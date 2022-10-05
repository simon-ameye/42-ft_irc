#include "../Server.hpp"

void			Server::_oper(std::vector<std::string> args, User &user)
{
	Channel channel;
	std::string name;
	std::string pass;
	std::string opername;
	std::string operpass;

	opername = OPERNAME;
	operpass = OPERPASS;

	//ERR_NOOPERHOST : not required
	if (args.size() < 2)
	{
		_errorReplies(user, ERR_NEEDMOREPARAMS, "OPER", channel);
		return;
	}

	name = args[0];
	pass = args[1];

	if (name != opername || pass != operpass)
	{
		_errorReplies(user, ERR_PASSWDMISMATCH, "OPER", channel);
		return;
	}

	user._operator = 1;
	_commandResponces(user, RPL_YOUREOPER, "OPER", channel);

}
