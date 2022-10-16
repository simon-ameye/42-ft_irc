#include "Server.hpp"

void Server::dispatch(const std::string &message, User &user)
{
	std::cout << user.getFullClientIdentifier() << " : $" << RED << message << RESET << "$" << std::endl;

	std::vector<std::string> splitCmd;
	std::string cmd;
	std::string args;

	splitCmd = Utils::split_cmd(message, ' ');
	cmd = _toupper(splitCmd[0]);
	args = splitCmd[1];

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
	else if (cmd == "DIE")
		_die(args, user);
	else if (cmd == "QUIT")
		_quit(args, user);
	else if (cmd == "KILL")
		_kill(args, user);
	else if (cmd == "REHASH")
		_rehash(args, user);
	else
		_errorReplies(user, ERR_UNKNOWNCOMMAND, cmd, "");

	_sendWelcome(user);
}
