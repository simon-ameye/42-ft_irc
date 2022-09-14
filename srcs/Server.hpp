#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>

#include <stdlib.h> //for atoi

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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
	int				sock;
	int				port;
	std::string		password;

};


#endif