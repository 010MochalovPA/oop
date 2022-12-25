#include <map>
#include <string>
#include "html_decode_headers.h"

std::map<std::string, std::string> mnemonics = { 
	{ "&quot;", "\"" },
	{ "&apos;", "\'" },
	{ "&lt;", "<" },
	{ "&gt;", ">"},
	{ "&amp;", "&" },
};

//	если много амперсонов подряд. ТО ПРОГРАММА БУДЕТ работать медленно

std::string HtmlDecode(const std::string& html) 
{
	size_t position = 0;

	std::string result;

	std::string mnemonic;

	while (position < html.length())
	{
		size_t foundPos = html.find("&", position);

		if (foundPos != std::string::npos)
		{
			result.append(html, position, foundPos - position);

			position = foundPos;

			size_t mnemonicEnd = html.find(";", position);
			
			mnemonic = html.substr(position, mnemonicEnd - foundPos + 1);

			if (mnemonics.find(mnemonic) != mnemonics.end())
			{
				result.append(mnemonics[mnemonic]);
				position = position + mnemonic.length();
			}
			else
			{
				result.append("&");
				position++;	
			}
		}
		else
		{
			result.append(html, position);
			position = html.length();
		}

	}

	return result;
}

void DecodeInputStream(std::istream& inputStream, std::ostream& outputStream)
{
	std::string line;

	while (std::getline(inputStream, line))
	{
		outputStream << HtmlDecode(line) << std::endl;
	}
}


