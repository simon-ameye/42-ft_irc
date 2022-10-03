#ifndef SERVER_HPP
#define SERVER_HPP

#include "../Utils/Utils.hpp"

#include "User/User.hpp"
//#include "Commands/Commands.hpp"
#include "ServerSettings.hpp"
//#include "Commands/CommandSrcs/Nick.hpp"
//#include "Commands/ACommand.hpp"
#include "ErrorReplies.hpp"
#include "CommandResponses.hpp"

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

class User;

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
	void			processCmd(std::string& cmd, User& user);
	bool			hasUser(std::string nick);

	private:
	int				_port;
	std::string		_password;
	sockaddr_in		_sin;
	socklen_t		_sizeofsin;
	int				_exitSignal;
	int				_masterSocket;
	std::map<int, User> _users;
	std::vector<pollfd>	_pollfds;

	private:
	void			_nick(std::vector<std::string> tokens, User &user);
};

#endif