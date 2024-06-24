#pragma once

#include "HttpUrl.h"
#include <regex>
#include <string>
#include <string_view>
#include <iostream>

namespace
{
	std::regex REGEX_URL("([a-zA-Z]+)://([\\w.]+)(:(\\d+))?(/([^\\s]+))?"); // любой регистр ++

	constexpr unsigned int MIN_PORT = 1;
	constexpr unsigned int MAX_PORT = 65535; // 65537 пропускает ++
	}

HttpUrl::HttpUrl(const std::string& url)
{
	std::smatch result;
	if (!std::regex_match(url, result, REGEX_URL))
	{
		throw UrlParsingError("Invalid URL");
	}

	try
	{
		m_protocol = StringToProtocol(result[1]);
		m_domain = result[2];
		m_port = result[4].matched ? ParsePort(result[4]) : DEFAULT_PORT.at(m_protocol);
		m_document = ParseDocument(result[5].str());
		m_url = BuildURL(m_domain, m_document, m_protocol, m_port);
	}
	catch(std::invalid_argument ex)
	{
		throw UrlParsingError(ex.what());
	}
}

HttpUrl::HttpUrl(const std::string& domain, const std::string& document, Protocol protocol)
	: HttpUrl(domain, document, protocol, DEFAULT_PORT.at(protocol))
{
}

HttpUrl::HttpUrl(const std::string& domain, const std::string& document, Protocol protocol, unsigned int port)
{
	try
	{
		m_domain = domain;
		m_document = ParseDocument(document);
		m_protocol = protocol;
		m_port = ValidatePort(port);
		m_url = BuildURL(m_domain, m_document, m_protocol, m_port);
	}
	catch (const std::invalid_argument& ex)
	{
		throw UrlParsingError(ex.what());
	}
}

std::string HttpUrl::BuildURL(const std::string& domain, const std::string& document, Protocol protocol, unsigned int port)
{
	const std::string urlPort = port == DEFAULT_PORT.at(protocol) ? "" : ":" + std::to_string(ValidatePort(port)); // можно сконструировать с нулевым портом? ++

	return PROTOCOL_STRING.at(protocol) + "://" + domain + urlPort + document;
}

Protocol HttpUrl::StringToProtocol(const std::string& protocol)
{
	std::string result(protocol);

	std::transform(result.begin(), result.end(), result.begin(),
		[](unsigned char ch) {
			return std::tolower(ch);
		});

	std::string_view protocolView(result);

	if (protocolView == "http")
	{
		return Protocol::HTTP;
	}

	if (protocolView == "https")
	{
		return Protocol::HTTPS;
	}
	
	if (protocolView == "ftp")
	{
		return Protocol::FTP;
	}
	
	throw UrlParsingError("Invalid protocol");
}

unsigned int HttpUrl::ParsePort(const std::string& portString)
{
	if (empty(portString))
	{
		throw UrlParsingError("Invalid Port");
	}

	unsigned int port = stoi(portString);

	return ValidatePort(port);
}

unsigned int HttpUrl::ValidatePort(unsigned int port)
{
	if (port < MIN_PORT || port > MAX_PORT)
	{
		throw UrlParsingError("Invalid Port");
	}

	return port;
}

std::string HttpUrl::ParseDomain(const std::string& domain)
{
	if (empty(domain))
	{
		throw UrlParsingError("Invalid Domain");
	}

	return domain;
}
std::string HttpUrl::ParseDocument(const std::string& document)
{
	return document[0] != '/' ? "/" + document : document;
}
	

std::string HttpUrl::GetURL() const
{
	return m_url;
}

std::string HttpUrl::GetDomain() const
{
	return m_domain;
}

std::string HttpUrl::GetDocument() const
{
	return m_document;
}

Protocol HttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned int HttpUrl::GetPort() const
{
	return m_port;
}