#include <map>
#include <string>
#include "html_decode_headers.h"
// Обьявить как const ++
const std::map<std::string, std::string> mnemonics = { 
	{ "&quot;", "\"" },
	{ "&apos;", "\'" },
	{ "&lt;", "<" },
	{ "&gt;", ">"},
	{ "&amp;", "&" },
};

const size_t MAX_MNEMONIC_LENGTH = 5;
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

			size_t lengthToEnd = html.length() - foundPos - 1;

			size_t subStringEnd = std::min(lengthToEnd, MAX_MNEMONIC_LENGTH);

			std::string subString = html.substr(foundPos, subStringEnd);

			position = foundPos;

			size_t mnemonicEnd = subString.find(";");
			
			mnemonic = html.substr(position, mnemonicEnd);
			
			if (mnemonics.find(mnemonic) != mnemonics.end())
			{
				std::string findMnemonic = (*mnemonics.find(mnemonic)).second;
				result.append(findMnemonic);
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
			break;
			// КАК будто можно выполнть аппенд сразу;
			// МОЖНО СДЕЛАТЬ БРЕЙК
		}

	}

	result.append(html, position);

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


