#include "Server.hpp"

void Server::_commandResponces(User &user, int rpl, std::string cmd, Channel &channel)
{
	(void) cmd;
	(void) channel;
	std::stringstream result;

	result << ":" << _serverName << " ";
	result << rpl << " ";

	switch (rpl)
	{
		case 381:
			result << ":You are now an IRC operator";
			break;
		default:
			result << "Unknown reply";
			
	}
	result << DELIMITER;
	user.outputBuffer += result.str();
}
