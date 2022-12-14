#include "Server.hpp"

void Server::dispatch(const std::string &message, User &user)
{
	std::cout << user.getFullClientIdentifier() << " : $" << RED << message << RESET << "$" << std::endl;

	std::vector<std::string> splitCmd = Utils::split_cmd(message, ' ');

	std::string cmd = _toupper(splitCmd[0]);
	std::string args = splitCmd[1];

	if (cmd == "")
		std::cout << "empty cmd" << std::endl;
	else if (cmd == "CAP") //empty comnmand just used not to send error uknown
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
	else if (cmd == "NOTICE")
		_notice(args, user);
	else if (cmd == "MODE") //empty comnmand just used not to send error uknown
		_mode(args, user);
	else if (cmd == "DIE")
		_die(args, user);
	else if (cmd == "QUIT")
		_quit(args, user);
	else if (cmd == "KILL")
		_kill(args, user);
	else if (cmd == "REHASH")
		_rehash(args, user);
	else if (cmd == "RESTART")
		_restart(args, user);
	else if (cmd == "PART")
		_part(args, user);
	else if (cmd == "TOPIC")
		_topic(args, user);
	else
		_errorReplies(user, ERR_UNKNOWNCOMMAND, cmd, "");

	_sendWelcome(user);
}
