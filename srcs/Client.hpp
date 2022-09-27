#ifndef CLIENT_HPP
#define CLIENT_HPP

/*Basics*/
#include <iostream>

class Client
{
	public:
	Client();
	~Client();
	Client &newClient();

	public:
	int				_sock;

};

#endif