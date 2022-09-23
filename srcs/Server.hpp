#ifndef SERVER_HPP
#define SERVER_HPP

#include "Client.hpp"

/*Basics*/
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/*Socket requirements*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Server
{
	public:
	Server();
	~Server();
	//init();
	//exec();

	public:
	void setPort(char *str);
	void setPassword(char *str);

	private:
	int				_sock;
	int				_port;
	std::string		_password;
	sockaddr_in		_sin;
	int				_sizeofsin;

};


#endif