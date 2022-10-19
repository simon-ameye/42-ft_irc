#include "../Server.hpp"

void Server::_topic(std::string args, User &user)
{
	/*----------------command protect------------------*/
	if (!user.getIsRegistered())
		return;
	/*----------------command protect------------------*/

	std::string channel;
	std::string topic;

	try { channel = Utils::split(args, ' ').at(0); }
	catch(...) { return _errorReplies(user, ERR_NEEDMOREPARAMS, "PRIVMSG", ""); }

	if (!user.isInChannel(channel))
		return _errorReplies(user, ERR_NOTONCHANNEL, "TOPIC", "");

	size_t pos = args.find(':');
	if (pos != std::string::npos) //a topic name is given. It can be empty
	{
		topic = args;
		topic.erase(0, pos + 1);
		findChannel(channel)->setTopic(topic);
	}
	return _commandResponces(user, RPL_TOPIC, "JOIN", "", *findChannel(channel)); //anyway, we reply with topic
}