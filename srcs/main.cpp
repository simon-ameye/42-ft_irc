#include "Server/Server.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "./ircserv <port> <password>" << std::endl;
		return 1;
	}
	Server server(argv[1], argv[2]);
	while (!server.getExitSignal())
	{
		server.connect();
		server.getMessages();
		server.processMessages();
		server.sendMessage();
		sleep(1);
	}
}