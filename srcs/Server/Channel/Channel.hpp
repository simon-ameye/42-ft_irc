#ifndef CHANNEL_HPP
#define CHANNEL_HPP

/*Basics*/
#include <iostream>
#include <vector>

#include "../ServerSettings.hpp"

class Channel
{
private:
	std::string _channelName;
	std::string _topic;

public:
	Channel(void);
	Channel(std::string channelName);
	~Channel(void);
	std::string getName() const;
	std::string getTopic() const;

	// std::vector<std::string> _users;
private:
};

#endif