#include "Server.hpp"

void Server::dispatch(const std::string &message, User &user)
{
	std::cout << "Processing command : $" << message << "$" << std::endl;

	std::vector<std::string> splitCmd;
	std::string cmd;
	std::string args;

	splitCmd = Utils::split_cmd(message, ' ');
	cmd = splitCmd[0];
	args = splitCmd[1];

	std::cout << "cmd : $" << cmd << "$" << std::endl;
	std::cout << "args : $" << args << "$" << std::endl;

	if (cmd == "")
		std::cout << "empty cmd" << std::endl;
	else if (cmd == "CAP")
		_cap(args, user);
	else if (cmd == "NICK")
		_nick(args, user); 
	else if (cmd == "PASS")
		_pass(args, user);
	else if (cmd == "PING")
		_ping(args, user);
	else if (cmd == "OPER")
		_oper(args, user);
	else if (cmd == "USER")
		_user(args, user);
	else if (cmd == "JOIN")
		_join(args, user);
	else if (cmd == "PRIVMSG")
		_privmsg(args, user);
	else if (cmd == "MODE")
		_mode(args, user);
	else if (cmd == "die")
		_die(args, user);
	else
	{
		Channel channel; //useless, just used to pass to _errorReplies
		_errorReplies(user, ERR_UNKNOWNCOMMAND, cmd, channel);
	}
}
