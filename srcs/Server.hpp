#ifndef SERVER_HPP
#define SERVER_HPP

#include "Client.hpp"

/*Basics*/
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <vector>

/*Socket requirements*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

/*Poll*/
#include <poll.h>

class Server
{
	public:
	Server(char *port, char *password);
	~Server();
	//init();
	//exec();

	private:
	int				_sock;
	int				_port;
	std::string		_password;
	sockaddr_in		_sin;
	socklen_t		_sizeofsin;

	std::vector<pollfd>	_pollfds;
};


#endif