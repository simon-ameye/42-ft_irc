#ifndef SERVER_HPP
#define SERVER_HPP

/*Project headers*/
#include "../Utils/Utils.hpp"
#include "User/User.hpp"
#include "Channel/Channel.hpp"
#include "ServerSettings.hpp"
#include "ServerReplies/ErrorReplies.hpp"
#include "ServerReplies/CommandResponses.hpp"
#include "Config/Config.hpp"

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

/*Colors*/
#define RESET		"\033[0m"
#define RED			"\033[31m"
#define GREEN		"\033[32m"
#define YELLOW		"\033[33m"
#define BLUE		"\033[34m"

class User;

class Server
{
	/*Server constructors*/
	public:
	Server	(char *port, char *password);
	~Server	();

	/*Server attributes*/
	private:
	int						_exitSignal;
	int						_masterSocket;
	bool					_restartNeeded;
	Config					_confg;
	socklen_t				_sizeofsin;
	sockaddr_in				_sin;
	std::string				_password;
	std::string				_serverName;
	std::vector<User>		_users;
	std::vector<Channel>	_channels;
	std::vector<pollfd>		_pollfds;

	/*Server functions*/
	public:
	void		setRestartNeeded	(bool);
	bool		getRestartNeeded	();
	void		getNewUsers			();
	void		getMessages			();
	void		block				();
	void		dispatchs			();
	void		sendMessage			();
	void		clean				();
	void		refreshConfig		();
	void		exitServer			(const std::string &message, int exitCode);
	void		dispatch			(const std::string& message, User& user);
	Config		&getConfig			();
	const int	&getExitSignal		();

	/*ServerUtils*/
	public:
	bool										hasUser				(std::string nickName, std::string exclude = "");
	bool										hasChannel			(std::string channelName);
	void										deleteChannel		(std::string channelName);
	void										debug				();
	std::vector<User>::iterator					findUser			(std::string nickName);
	std::vector<User>::iterator					getUserItByFd		(int fd);
	std::vector<Channel>::iterator				findChannel			(std::string channelName);
	std::vector<std::vector<User>::iterator>	getUsersInChannel	(std::string channelName);

	/*ServerUtils*/
	private:
	bool		_sendPrivMessageToChannel	(std::string channel, std::string message, std::string sender, const std::string &excludeUser);
	bool		_sendPrivMessageToUser		(std::string recipient, std::string message, std::string sender);
	void		_clearDeletedUsers			();
	void		_removeEmptyChannels		();
	void		_sendWelcome				(User &user);
	void		_sendMessageToChannel		(std::string channel, std::string message, const std::string &excludeUser = std::string());
	void		_sendMessageToChannels		(std::vector<std::string> channels, std::string message);
	std::string	_toupper					(const std::string &str);

	/*Utils in JOIN*/
	private:
	void	_nameReply	(User &user, std::string channelName);
	void	_joinReply	(User &user, std::string channelName);

	/*Standard replies*/
	private:
	void	_errorReplies		(User &user, int err, std::string cmd, std::string str, const Channel &channel = Channel());
	void	_commandResponces	(User &user, int rpl, std::string cmd, std::string str, const Channel &channel = Channel());

	/*Commands*/
	private:
	void	_cap		(std::string args, User &user);
	void	_die		(std::string args, User &user);
	void	_nick		(std::string args, User &user);
	void	_pass		(std::string args, User &user);
	void	_oper		(std::string args, User &user);
	void	_user		(std::string args, User &user);
	void	_ping		(std::string args, User &user);
	void	_join		(std::string args, User &user);
	void	_mode		(std::string args, User &user);
	void	_quit		(std::string args, User &user);
	void	_privmsg	(std::string args, User &user);
	void	_notice		(std::string args, User &user);
	void	_kill		(std::string args, User &user);
	void	_rehash		(std::string args, User &user);
	void	_restart	(std::string args, User &user);
	void	_part		(std::string args, User &user);
	void	_topic		(std::string args, User &user);
};
#endif
