#include "../Server.hpp"

void Server::_errorReplies(User &user, int err, std::string cmd, const Channel &channel, const std::string &optionalString)
{
	std::stringstream result;

	result << ":" << _serverName << " ";
	result << Utils::getCode(err) << " ";

	switch (err)
	{
	case ERR_NOSUCHNICK:
		result << user.getNickName() << " :No such nick/channel";
		break;
	case ERR_NOSUCHSERVER:
		result << _serverName << " :No such server";
		break;
	case ERR_NOSUCHCHANNEL:
		result << channel.getName() << " :No such server";
		break;
	case ERR_CANNOTSENDTOCHAN:
		result << channel.getName() << " :Cannot send to channel";
		break;
	case ERR_TOOMANYCHANNELS:
		result << channel.getName() << " :You have joined too many channels";
		break;
	case ERR_WASNOSUCHNICK:
		result << user.getNickName() << " :There was no such nickname";
		break;
	case ERR_UNKNOWNCOMMAND:
		result << cmd << " :Unknown command";
		break;
	case ERR_NONICKNAMEGIVEN:
		result << " :No nickname given";
		break;
	case ERR_ERRONEUSNICKNAME:
		result << " :Erroneus nickname";
		break;
	case ERR_NICKNAMEINUSE:
		result << optionalString << " :Nickname is already in use";
		break;
	case ERR_NEEDMOREPARAMS:
		result << cmd << " :Not enough parameters";
		break;
	case ERR_ALREADYREGISTRED:
		result << ":Unauthorized command (already registered)";
		break;
	case ERR_PASSWDMISMATCH:
		result << ":Password incorrect";
		break;
	case ERR_NOPRIVILEGES:
		result << ":You havn't user rights";
		break;

	default:
		result << "Unknown error";
	}
	user.addOutputMessage(result.str());
}
