#ifndef CHANNEL_HPP
#define CHANNEL_HPP

/*Basics*/
#include <iostream>
#include <vector>

#include "../ServerSettings.hpp"

class Channel
{
	public :
	std::string _channelName;
	std::vector<std::string> _users;
	private:
};

#endif