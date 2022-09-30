#include "Utils.hpp"

void Utils::clearBuffer(char *buffer, int size)
{
	for (int i = 0; i < size; i++)
		buffer[i] = '\0';
}