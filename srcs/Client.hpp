#ifndef CLIENT_HPP
#define CLIENT_HPP

/*Basics*/
#include <iostream>
#include <poll.h>

class Client
{
	public:
	Client();
	Client(int fd);
	~Client();
	Client &newClient();

	public:
	//int				_fd;
	std::string inputBuffer;
	std::string outputBuffer;

};

#endif