#include "./dictionary_functions.h"

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
		PrintTranslations(dictionary, outputFile, StringToLowerCase(word.first));
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
	
	bool willSave = false; // переименовать +

	StartChat(input, output, dictionary, willSave);

	if (willSave)
	{
		SaveDictionary(dictionaryPath, dictionary, output);
	}

}

void OutputChatMessage(std::ostream& output, const std::string message)
{
	output << "> " << message;
}

void StartChat(std::istream& input, std::ostream& output, Dictionary& dictionary, bool& willSave) // подумать, как разделить функц
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
				line.clear(); // использовать метод clear +
			}

			if (!Trim(line).empty()) //лучше использовать empty +
			{
				AddTranslation(dictionary, newWord, line);

				OutputChatMessage(output, "Слово \"" + newWord + "\" сохранено в словаре как - ");
				PrintTranslations(dictionary, output, newWord);
				willSave = true;
			}
			else
			{
				OutputChatMessage(output, "Слово \"" + newWord + "\" проигнорировано.\n");
			}

			newWord.clear();
			continue;
		}

		if (Trim(line) == "...")
		{
			if (willSave)
			{
				OutputChatMessage(output, "Сохранить - \"Y\"\n");

				getline(input, line);
				
				if (Trim(StringToLowerCase(line)) == "y")
				{
					break;
				}
				else
				{
					willSave = false;
				}
			}
			break;
		}

		if (!Trim(line).empty())
		{
			if (dictionary.find(StringToLowerCase(line)) != dictionary.end())
			{
				OutputChatMessage(output, "");
				PrintTranslations(dictionary, output, StringToLowerCase(line));
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

	for (unsigned char ch : str)
	{
		result += tolower(ch);// использовать с unsigned char +
	}

	return Trim(result);
}

void PrintTranslations(Dictionary& dictionary, std::ostream& output, const std::string word) //const если не модифицируем +
{
	
	// которые не модифицирует аргументы по константной ссылке (Dictionary& dictionary)

	std::string line;
	
	for (const std::string& translation : dictionary[word]) // копируется строка +
	{
		line = line + translation + ", ";
	 // найти более дешевый способ не печатать запяную в конце +
	}
	line.erase(line.size() - 2);
	output << line;
	output << std::endl;
}

Translations SplitStringIntoTranstations(std::string str, char separator) // передать str по const
{
	Translations translations;

	std::string translation;
	std::stringstream strStream(str);

	while (getline(strStream, translation, separator) || getline(strStream, translation))
	{
		translation = Trim(translation);
		// trim вызывается несколько раз +
		if (!translation.empty())
		{
			translations.insert(translation);
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
		dictionary.emplace(word, translations); // метод emplace и try_emplace для создания пары +
	}
}

void AddTranslation(Dictionary& dictionary, const std::string& word, const std::string& translations)
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