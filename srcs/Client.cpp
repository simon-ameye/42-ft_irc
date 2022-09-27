#include "Client.hpp"

Client::Client() {}

Client::~Client() {}

Client &Client::newClient()
{
	return *(new Client);
}
