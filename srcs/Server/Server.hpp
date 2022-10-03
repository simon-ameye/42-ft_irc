#ifndef SERVER_HPP
#define SERVER_HPP

#include "User.hpp"
#include "Utils.hpp"

#include "Nick.hpp"
#include "Command.hpp"
#include "Error_Replies.hpp"
#include "Command_Responses.hpp"

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

#define BUFFER_SIZE 5
#define DELIMITER "\r\n"

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
	std::string		processCmd(std::string& cmd, User& user);
	bool			hasUser(std::string nick);
	void			initCommands(void);

	private:
	int				_port;
	std::string		_password;
	sockaddr_in		_sin;
	socklen_t		_sizeofsin;
	int				_exitSignal;
	int				_masterSocket;
	std::map<int, User> _users;
	std::vector<pollfd>	_pollfds;
	std::map<std::string, Command> _commands;
};

#endif