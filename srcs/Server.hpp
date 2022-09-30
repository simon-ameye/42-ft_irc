#ifndef SERVER_HPP
#define SERVER_HPP

#include "Client.hpp"
#include "Utils.hpp"

/*Basics*/
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <map>

/*Socket requirements*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

/*Poll*/
#include <poll.h>

#define BUFFER_SIZE 10


class Server
{
	public:
	Server(char *port, char *password);
	~Server();
	void			connect(void);
	void			getData(void);
	void			processData(void);
	void			sendData(void);
	const int		&getExitSignal(void);

	private:
	int				_port;
	std::string		_password;
	sockaddr_in		_sin;
	socklen_t		_sizeofsin;
	int				_exitSignal;
	int				_masterSocket;
	std::map<int, Client> _clients;
	std::vector<pollfd>	_pollfds;
};


#endif