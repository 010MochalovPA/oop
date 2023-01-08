#include "url_parser.h"

void RunCheckURL(std::istream& input, std::ostream& output) {
	std::string line;

	while (input >> line)
	{
		URL url = { line };

		if (ParseURL(url.url, url.protocol, url.port, url.host, url.document))
		{
			PrintURL(url, output);
			continue;
		}

		output << "Invalid URL! Usage: protocol://host[:port(1-65535)][/document]" << std::endl;
	}
}

bool ParseURL(std::string const& url, Protocol& protocol, unsigned int& port, std::string& host, std::string& document) {
	std::cmatch result;
	std::regex reg("^(HTTPS|HTTP|FTP|https|http|ftp):\\/\\/([\\w\\.]+)(:([\\d]+))?((\\/[^\\/]+)+\\/?)?$");

	if (std::regex_search(url.c_str(), result, reg))
	{
		protocol = GetProtocolFromString(result[1]);

		host = result[2];
		
		port = GetPortFromString(result[4], protocol);
		
		if (port == 0 || port > 65535)
		{
			return false;
		}
		
		document = result[5];

		return true;
	}
	return false;
}

Protocol GetProtocolFromString(std::string protocol) {

	std::transform(protocol.begin(), protocol.end(), protocol.begin(), [](const char ch) {
		return std::tolower(ch);
	});

	if (protocol == "https")
	{
		return Protocol::HTTPS;
	}

	if (protocol == "http")
	{
		return Protocol::HTTP;
	}

	if (protocol == "ftp")
	{
		return Protocol::FTP;
	}

	return Protocol::HTTPS;
}

int GetPortFromString(std::string port, Protocol protocol){

	if (port.empty())
	{
		return (int)protocol;
	}

	return stoi(port);
}

void PrintURL(const URL& url, std::ostream& output)
{
	output << std::endl;
	output << url.url << std::endl;
	output << "HOST: " << url.host << std::endl;
	output << "PORT: " << url.port << std::endl;
	output << "DOC: " << url.document << std::endl;
}