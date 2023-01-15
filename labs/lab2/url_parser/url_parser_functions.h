#pragma once

#include <iostream>
#include <regex>
#include <optional>

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

bool ParseURL(std::string const& url, Protocol& protocol, unsigned int& port, std::string& host, std::string& document);
void PrintURL(const URL& url, std::ostream& outputStream);
std::optional<Protocol> GetProtocolFromString(std::string protocol);
int GetPortFromString(const std::string& port, const Protocol& protocol);