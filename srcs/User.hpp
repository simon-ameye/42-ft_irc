#ifndef CLIENT_HPP
#define CLIENT_HPP

/*Basics*/
#include <iostream>
#include <poll.h>
#include <vector>

//#define DELIMITER "\r\n"
#define DELIMITER "\r\n"

class User
{
	public:
	User();
	~User();
	User &newUser();
	void addCmdBuffer(char *buffer, size_t size);

	public:
	//int				_fd;
	std::vector<std::string> inputMessages;
	std::string inputBuffer;
	std::string outputBuffer;

};

#endif