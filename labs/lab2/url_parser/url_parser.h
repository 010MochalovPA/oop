#pragma once

#include <iostream>
#include <regex>

enum class Protocol
{
	FTP = 21,
	HTTP = 80,
	HTTPS = 443,
};

struct URL
{
	std::string url;
	Protocol protocol;
	std::string host;
	unsigned int port;
	std::string document;
};

void RunCheckURL(std::istream& inputStream, std::ostream& outputStream);
bool ParseURL(std::string const& url, Protocol& protocol, unsigned int& port, std::string& host, std::string& document);
void PrintURL(const URL& url, std::ostream& outputStream);
Protocol GetProtocolFromString(std::string protocol);
int GetPortFromString(std::string port, Protocol protocol);