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
	void addCmdBuffer(char *buffer, size_t size);
	std::string realName; //to set private + getter
	std::string nickName; //to set private + getter

	public:
	std::vector<std::string> inputMessages; //to set private + getter
	std::string inputBuffer; //to set private + getter
	std::string outputBuffer; //to set private + getter
	bool		_passProvided; //to set private + getter
};

#endif