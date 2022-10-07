#ifndef SERVER_HPP
#define SERVER_HPP

#include "../Utils/Utils.hpp"

#include "User/User.hpp"
#include "Channel/Channel.hpp"
#include "ServerSettings.hpp"
#include "ServerReplies/ErrorReplies.hpp"
#include "ServerReplies/CommandResponses.hpp"

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
	void			getMessages(void);
	void			processMessages(void);
	void			sendMessage(void);
	const int		&getExitSignal(void);
	void			processMessage(std::string& message, User& user);
	bool			hasUser(std::string nickName, std::string exclude = "");
	bool			hasChannel(std::string channelName);
	void			deleteUser(std::string nickName);
	void			deleteChannel(std::string channelName);
	std::vector<Channel>::iterator findChannel(std::string channelName);

	

	private:
	int				_port;
	std::string		_password;
	sockaddr_in		_sin;
	socklen_t		_sizeofsin;
	int				_exitSignal;
	int				_masterSocket;
	std::map<int, User> _users;
	std::vector<Channel> _channels;
	std::vector<pollfd>	_pollfds;
	std::string _serverName;

	private:
	void			_nick(std::string args, User &user);
	void			_pass(std::string args, User &user);
	void			_oper(std::string args, User &user);
	void			_errorReplies(User &user, int err, std::string cmd, const Channel &Channel, const std::string &optionalString = std::string());
	void			_commandResponces(User &user, int rpl, std::string cmd, Channel &channel);
	void			_user(std::string args, User &user);
	void			_ping(std::string args, User &user);
	void			_privmsg(std::string args, User &user);
	void			_join(std::string args, User &user);
	void			_cap(std::string args, User &user);
};

#endif