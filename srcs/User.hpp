#ifndef CLIENT_HPP
#define CLIENT_HPP

/*Basics*/
#include <iostream>
#include <poll.h>
#include <vector>

#include "Server.hpp"

class User
{
	public:
	User();
	~User();
	User &newUser();
	void addCmdBuffer(char *buffer, size_t size);

	public:
	std::vector<std::string> inputMessages;
	std::string inputBuffer;
	std::string outputBuffer;
};

#endif