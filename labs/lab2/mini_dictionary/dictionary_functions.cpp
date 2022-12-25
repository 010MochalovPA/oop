#include "./mini_dictionary.h"

std::string Trim(std::string str)
{
	str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
	}).base(), str.end());

	str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
		return !std::isspace(ch);
	}));

	return str;
}

void SaveDictionary(const std::string dictionaryPath, Dictionary& dictionary, std::ostream& output)
{
	std::ofstream outputFile(dictionaryPath);

	if (!outputFile.is_open())
	{
		throw std::exception("Error save dictionary!");
	}

	CopyDictionaryToFile(outputFile, dictionary);
}

void CopyDictionaryToFile(std::ofstream& outputFile, Dictionary& dictionary)
{
	for (auto word : dictionary)
	{
		outputFile << word.first << " - ";
		PringTranslations(dictionary, outputFile, StringToLowerCase(word.first));
	}
}

void RunDictionary(std::istream& input, std::ostream& output, std::string dictionaryPath)
{
	std::ifstream dictionaryFile(dictionaryPath);

	Dictionary dictionary = {};

	if (dictionaryFile.is_open())
	{
		dictionary = GetDictionaryFromFile(dictionaryFile);
	}

	dictionaryFile.close();
	
	bool dictionaryChanged = false;

	StartChat(input, output, dictionary, dictionaryChanged);

	if (dictionaryChanged)
	{
		SaveDictionary(dictionaryPath, dictionary, output);
	}

}

void OutputChatMessage(std::ostream& output, const std::string message)
{
	output << "> " << message;
}

void StartChat(std::istream& input, std::ostream& output, Dictionary& dictionary, bool& dictionaryChanged)
{
	std::string line;
	std::string newWord;

	while (getline(input, line))
	{
		if (!newWord.empty())
		{
			Translations translationsSet = SplitStringIntoTranstations(line, ',');

			if (translationsSet.empty())
			{
				line = "";
			}

			if (Trim(line) != "")
			{
				AddTranslation(dictionary, newWord, line);

				OutputChatMessage(output, "Слово \"" + newWord + "\" сохранено в словаре как - ");
				PringTranslations(dictionary, output, newWord);
				dictionaryChanged = true;
			}
			else
			{
				OutputChatMessage(output, "Слово \"" + newWord + "\" проигнорировано.\n");
			}

			newWord = "";
			continue;
		}

		if (Trim(line) == "...")
		{
			if (dictionaryChanged)
			{
				OutputChatMessage(output, "Сохранить - \"Y\"\n");

				getline(input, line);
				
				if (Trim(StringToLowerCase(line)) == "y")
				{
					break;
				}
				else
				{
					dictionaryChanged = false;
				}
			}
			break;
		}

		if (Trim(line) != "")
		{
			if (dictionary.find(StringToLowerCase(line)) != dictionary.end())
			{
				OutputChatMessage(output, "");
				PringTranslations(dictionary, output, StringToLowerCase(line));
			}
			else
			{
				OutputChatMessage(output, "Неизвестное слово \"" + line + "\". Введите перевод или пустую строку для отказа.\n");
				newWord = line;
			}
		}
	}
}

std::string StringToLowerCase(const std::string& str)
{
	std::string result;

	for (auto ch : str)
	{
		result += tolower(ch);
	}

	return Trim(result);
}

void PringTranslations(Dictionary& dictionary, std::ostream& output, std::string word)
{
	for (std::string translation : dictionary[word])
	{
		output << translation;

		if (translation != *dictionary[word].rbegin())
		{
			output << ", ";
		}
	}

	output << std::endl;
}

Translations SplitStringIntoTranstations(std::string str, char separator)
{
	Translations translations;

	std::string translation;
	std::stringstream strStream(str);

	while (getline(strStream, translation, separator) || getline(strStream, translation))
	{
		if (!Trim(translation).empty())
		{
			translations.insert(Trim(translation));
		}
	}
	return translations;
}

void InsertInDictionary(Dictionary& dictionary, const std::string& word, const Translations& translations)
{
	if (translations.empty())
	{
		return;
	}
	
	auto it = dictionary.find(word);
	if (it != dictionary.end())
	{
		for (std::string translation : translations)
		{
			it->second.insert(translation);
		}
	}
	else
	{
		std::pair<std::string, Translations> newValue = { word, translations };
		dictionary.insert(newValue);
	}
}

void AddTranslation(Dictionary& dictionary, const std::string word, const std::string translations)
{
	if (!word.empty() && !translations.empty())
	{
		std::string wordToLowerCase = StringToLowerCase(word);
		std::string translationsToLowerCase = StringToLowerCase(translations);
		Translations translationsSet = SplitStringIntoTranstations(translationsToLowerCase, ','); 

		InsertInDictionary(dictionary, wordToLowerCase, translationsSet);

		for (auto translation : translationsSet)
		{
			InsertInDictionary(dictionary, translation, SplitStringIntoTranstations(wordToLowerCase, ','));
		}
	}
}

Dictionary GetDictionaryFromFile(std::ifstream& input)
{
	Dictionary dictionary = {};

	std::string line;

	while (getline(input, line))
	{
		
		std::string word;
		std::string translations;

		std::stringstream lineStream(line);

		getline(lineStream, word, '-');
		getline(lineStream, translations);

		AddTranslation(dictionary, word, translations);
		
	}
	
	return dictionary;
}