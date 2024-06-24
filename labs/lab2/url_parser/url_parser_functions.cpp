#include "url_parser_functions.h" //������������ ���� � ���� � ����������� ������ ����� ���� ���������� ����� ����� +


bool ParseURL(std::string const& url, Protocol& protocol, unsigned int& port, std::string& host, std::string& document) {
	std::cmatch result;
	
	std::regex reg("^([\w.]+)" //(1-protocol) ����� ������� +
				   "://" // (://)
				   "([\w.]+)" // (2-host)
				   "(:(\d+))?" // (3-:port(4-port))
				   "(\/([^\s]+)))?)$" // (5-document)
	);

	if (std::regex_search(url.c_str(), result, reg))
	{
		auto optProtocol = GetProtocolFromString(result[1]);

		if (!optProtocol.has_value())
		{
			return false;
		}

		protocol = optProtocol.value();

		host = result[2];
		
		port = GetPortFromString(result[4], protocol);
		
		if (port == 0 || port > 65535) // �� ����������� ��������� �������� ������
		{
			return false;
		}
		
		document = result[5]; // ��������� / + 

		return true;
	}
	return false;
}

std::optional<Protocol> GetProtocolFromString(std::string protocol) {

	std::transform(protocol.begin(), protocol.end(), protocol.begin(), [](unsigned char ch) {
		return std::tolower(ch);// ��������� unsigned char � tolower +
	});

	if (protocol == "https")
	{
		return { Protocol::HTTPS };
	}

	if (protocol == "http")
	{
		return { Protocol::HTTP };
	}

	if (protocol == "ftp")
	{
		return { Protocol::FTP };
	}

	return std::nullopt;
}

//  �������� �� ������, ���� ����� �������������� +
int GetPortFromString(const std::string& port, const Protocol& protocol)
{
	if (port.empty())
	{
		// ������������ static_cast
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