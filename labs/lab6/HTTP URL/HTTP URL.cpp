#include <iostream>
#include <regex>
#include "HttpUrl.h"

int main()
{
	std::string line;

	while (std::getline(std::cin, line))
	{
		try
		{
			HttpUrl url(line);

			std::cout << "URL: " << url.GetURL() << std::endl;
			std::cout << "Protocol: " << PROTOCOL_STRING.at(url.GetProtocol()) << std::endl;
			std::cout << "Domain: " << url.GetDomain() << std::endl;
			std::cout << "Port: " << url.GetPort() << std::endl;
			std::cout << "Document: " << url.GetDocument()
					  << std::endl
					  << std::endl;
		}
		catch (const UrlParsingError& ex)
		{
			std::cout << ex.what() << std::endl;
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}

	return 0;
}