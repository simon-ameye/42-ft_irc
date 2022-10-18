#include "../Server.hpp"

void Server::_commandResponces(User &user, int rpl, std::string cmd, std::string str, const Channel &channel)
{
	(void)cmd;
	(void)channel;
	(void)str;
	std::stringstream result;

	result << ":" << _serverName << " " << Utils::getCode(rpl) << " " << user.getNickName();
	switch (rpl)
	{
	case RPL_WELCOME:
		result << " :YOOOOO ! Welcome to our Internet Relay Chat Network " << user.getFullClientIdentifier();
		break;
	case RPL_TOPIC:
		result << " " << channel.getName() << " :" << channel.getTopic();
		break;
	case RPL_ENDOFNAMES:
		result << " :" << channel.getName() << " :End of /NAMES list";
		break;
	case RPL_YOUREOPER:
		result << " :You are now an IRC operator";
		break;
	case RPL_REHASHING:
		result << " " << user.getFullClientIdentifier() << " config.ini " << ":REHASHING";
		break;
	default:
		result << " :Unknown reply";
	}
	user.addOutputMessage(result.str());
}
