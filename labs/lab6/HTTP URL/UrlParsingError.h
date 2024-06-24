#pragma once

#include <stdexcept>
#include <string>

class UrlParsingError : public std::invalid_argument
{
public:
	UrlParsingError(const std::string& message)
		: std::invalid_argument(message)
	{
	}
};
