#ifndef SERVER_HPP
#define SERVER_HPP

#include "../Utils/Utils.hpp"

#include "User/User.hpp"
#include "Channel/Channel.hpp"
#include "ServerSettings.hpp"
#include "ErrorReplies.hpp"
#include "CommandResponses.hpp"

/*Basics*/
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <sstream>

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
	std::map<int, Channel> _channels;
	std::vector<pollfd>	_pollfds;
	std::string _serverName;

	private:
	void			_nick(std::vector<std::string> tokens, User &user);
	void			_pass(std::vector<std::string> tokens, User &user);
	void			_oper(std::vector<std::string> tokens, User &user);
	void			_errorReplies(User &user, int err, std::string cmd, Channel &channel);
	void			_commandResponces(User &user, int rpl, std::string cmd, Channel &channel);
};

#endif