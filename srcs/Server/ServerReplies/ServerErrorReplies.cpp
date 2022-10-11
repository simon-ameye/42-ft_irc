#include "../Server.hpp"

void Server::_errorReplies(User &user, int err, std::string cmd, const Channel &channel, const std::string &optionalString)
{
	std::stringstream result;

	result << ":" << _serverName << " ";
	result << Utils::getCode(err) << " ";

	switch (err)
	{
	case 401:
		result << user.getNickName() << " :No such nick/channel";
		break;
	case 402:
		result << _serverName << " :No such server";
		break;
	case 403:
		result << channel.getName() << " :No such server";
		break;
	case 404:
		result << channel.getName() << " :Cannot send to channel";
		break;
	case 405:
		result << channel.getName() << " :You have joined too many channels";
		break;
	case 406:
		result << user.getNickName() << " :There was no such nickname";
		break;
	case 421:
		result << cmd << " :Unknown command";
		break;
	case 431:
		result << " :No nickname given";
		break;
	case 432:
		result << " :Erroneus nickname";
		break;
	case 433:
		result << optionalString << " :Nickname is already in use";
		break;
	case 461:
		result << cmd << " :Not enough parameters";
		break;
	case 462:
		result << ":Unauthorized command (already registered)";
		break;
	case 464:
		result << ":Password incorrect";
		break;
	case 465:
		result << ":You havn't user rights";
		break;

	default:
		result << "Unknown error";
	}
	user.addOutputMessage(result.str());
}
