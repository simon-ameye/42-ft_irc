#include "Server/Server.hpp"
#include <iostream>

#define EXIT 0
#define RESTART 1

int start(char *port, char *password)
{
	Server server(port, password);
	while (!server.getExitSignal())
	{
		//poll
		server.block();
		server.getNewUsers();
		server.getMessages();
		server.dispatchs();
		server.sendMessage();
		server.clean();
		//usleep(100000);
	}
	if (server.getRestartNeeded())
		return RESTART;
	return EXIT;
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "./ircserv <port> <password>" << std::endl;
		return 1;
	}

	while (start(argv[1], argv[2]) == RESTART)
	{
		std::cout << "Restarting " << std::endl;
	}

	return (EXIT);
}