#pragma once

#include <stdexcept>
#include <string>
#include "UrlParsingError.h"
#include <map>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP,
};

const std::map<Protocol, unsigned int> DEFAULT_PORT = {
	{ Protocol::HTTP, 80 },
	{ Protocol::HTTPS, 443 },
	{ Protocol::FTP, 21 }
};

const std::map<Protocol, std::string> PROTOCOL_STRING = {
	{ Protocol::HTTP, "http" },
	{ Protocol::HTTPS, "https" },
	{ Protocol::FTP, "ftp" }
};

class HttpUrl
{
public:
	HttpUrl(const std::string& url);
	HttpUrl(const std::string& domain, const std::string& document, Protocol protocol = Protocol::HTTP);
	HttpUrl(const std::string& domain, const std::string& document, Protocol protocol, unsigned int port);
	
	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned int GetPort() const;

private:
	static Protocol StringToProtocol(const std::string& protocol);
	static unsigned int ParsePort(const std::string& port);
	static unsigned int ValidatePort(unsigned int port);
	static std::string ParseDomain(const std::string& domain);
	static std::string ParseDocument(const std::string& document);
	static std::string BuildURL(const std::string& domain, const std::string& document, Protocol protocol, unsigned int port);

	Protocol m_protocol;
	unsigned short m_port;
	std::string m_domain;
	std::string m_document;
	std::string m_url;
};