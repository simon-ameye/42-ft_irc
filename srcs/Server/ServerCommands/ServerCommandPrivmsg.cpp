#include "../Server.hpp"

static void sendChannelMesage(User &sender, User &recipient, std::string &message, std::string channelName)
{
	recipient.addOutputMessage(":" + sender.getNickName() + " PRIVMSG " + channelName + " :" + message);
}

void Server::_privmsg(std::string args, User &user)
{
	/*----------------command protect------------------*/
    if (!user.getIsRegistered())
		return;
	/*----------------command protect------------------*/

    std::vector<std::string> targets;
    std::string message;

    try
    {
	    targets = Utils::split(Utils::split(args, ':').at(0), ' ');
	    message = Utils::split(args, ':').at(1);
    }
    catch(const std::exception& e)
    {
		_errorReplies(user, ERR_NEEDMOREPARAMS, "PRIVMSG", "");
        return;
    }

	for (size_t i = 0; i < targets.size(); i++)
	{
		std::cout << "receveir[i] = " << targets[i] << std::endl;

        // message to users
		std::vector<User>::iterator it1 = findUser(targets[i]);
		if (it1 != _users.end())
		{
			it1->addOutputMessage(":" + user.getNickName() + " PRIVMSG " + it1->getNickName() + " :" + message);
		}

        // message to channel
		std::vector<Channel>::iterator it2 = findChannel(targets[i]);
		if (it2 != _channels.end())
		{
			std::vector<std::vector<User>::iterator> itUsers;
			itUsers = getUsersInChannel(targets[i]);
			for (size_t i = 0; i < itUsers.size(); i++)
			{
                // avoid sending message to sender
				if (user.getNickName() != itUsers[i]->getNickName())
					sendChannelMesage(user, *itUsers[i], message, it2->getName());
			}
		}
	}
}
