#ifndef CLIENT_HPP
#define CLIENT_HPP

/*Basics*/
#include <iostream>
#include <vector>

#include "../ServerSettings.hpp"

class User
{
	public:
	User();
	~User();
	User &newUser();
	void addBufferToMessages(char *buffer, size_t size);
	std::string realName; //to set private + getter
	std::string nickName; //to set private + getter
	std::string userName;
	std::string hostName;
	std::string serverName;
	bool		isRegistered;

	public:
	std::vector<std::string> _inputMessages; //to set private + getter
	std::string _inputMessagesBuffer; //to set private + getter
	std::string _outputMessage; //to set private + getter
	bool		_passProvided; //to set private + getter
	bool		_operator; //to set private + getter
};

#endif