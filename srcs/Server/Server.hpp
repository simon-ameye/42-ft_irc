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

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"

class User;

class Server
{
	public:
	Server(char *port, char *password);
	~Server();
	void			block(void);
	void			getNewUsers(void);
	void			getMessages(void);
	void			dispatchs(void);
	void			sendMessage(void);
	const int		&getExitSignal(void);
	void			dispatch(const std::string& message, User& user);


	std::vector<User>::iterator	getUserItByFd(int fd);
	bool			hasUser(std::string nickName, std::string exclude = "");
	bool			hasChannel(std::string channelName);
	void			deleteUser(std::string nickName);
	void			deleteChannel(std::string channelName);
	std::vector<Channel>::iterator findChannel(std::string channelName);
	std::vector<std::vector<User>::iterator> getUsersInChannel(std::string channelName);
	std::vector<User>::iterator			findUser(std::string nickName);
	void			nameReply(User &user, Channel &channel);
	void			joinReply(User &user, Channel &channel);


	private:
	std::string		_password;
	sockaddr_in		_sin;
	socklen_t		_sizeofsin;
	int				_exitSignal;
	int				_masterSocket;
	//std::map<int, User> _users;
	std::vector<User>		_users;
	std::vector<Channel>	_channels;
	std::vector<pollfd>		_pollfds;
	std::string _serverName;

	private:
	void			_nick(std::string args, User &user);
	void			_pass(std::string args, User &user);
	void			_oper(std::string args, User &user);
	void			_errorReplies(User &user, int err, std::string cmd, const Channel &Channel, const std::string &optionalString = std::string());
	void			_commandResponces(User &user, int rpl, std::string cmd, Channel &channel, const std::string &optionalString = std::string());
	void			_user(std::string args, User &user);
	void			_ping(std::string args, User &user);
	void			_privmsg(std::string args, User &user);
	void			_join(std::string args, User &user);
	void			_cap(std::string args, User &user);
	void			_mode(std::string args, User &user);
	void			_die(std::string args, User &user);

    void            _exit_server(const std::string &message, int exitCode);
};

#endif