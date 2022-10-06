#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <sstream>

class Utils
{
	public:
	static void clearBuffer(char *buffer, int size);
	static std::vector<std::string> split(std::string s, char delimiter);
	static std::vector<std::string> split_cmd(std::string str, char delimiter);
	static std::string getCode(int code);
};

#endif