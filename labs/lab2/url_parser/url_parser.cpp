#include "url_parser_functions.h"

int main()
{
	std::string line;

	while (std::cin >> line)
	{
		URL url = { line };

		if (ParseURL(url.url, url.protocol, url.port, url.host, url.document))
		{
			PrintURL(url, std::cout);
			continue;
		}

		std::cout << "Invalid URL! Usage: protocol://host[:port(1-65535)][/document]" << std::endl;
	}
}
