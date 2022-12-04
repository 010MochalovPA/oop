#include <fstream>
#include <string>
#include <iostream>

using namespace std;

struct Args
{
	string inputFileName;
	string outputFileName;
	string searchString;
	string replaceString;
};

string ReplaceString(const string& subject,
	const string& searchString, const string& replacementString);

void CopyFileWithReplacement(const string& inputFileName, const string& outputFileName,
	const string& searchString, const string& replacementString);

Args ParseArgs(const int, char*[]);
std::ifstream OpenInputFileStream(const std::string&);
std::string ConcatStringWithMessage(const std::string&);

Args ParseArgs(const int argc, char* argv[])
{
	if (argc != 5)
	{
		throw std::range_error("Invalid argument count");
	}

	Args args = {};
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.searchString = argv[3];
	args.replaceString = argv[4];

	return args;
}

std::ifstream OpenInputFileStream(const std::string& fileName)
{
	std::ifstream input(fileName, std::ios::binary);

	if (!input.is_open())
	{
		throw std::invalid_argument("Failed to open <input file> for reading");
	}

	return input;
}

std::ofstream OpenOutputFileStream(const std::string& fileName)
{
	std::ofstream output(fileName, std::ios::binary);

	if (!output.is_open())
	{
		throw std::invalid_argument("Failed to open <input file> for reading");
	}

	return output;
}

std::string ConcatStringWithMessage(const std::string& string)
{
	return string + '\n'
		+ "Usage: replace.exe <input file> <output file> <search string> <replace string>" + '\n';
}

// Возвращает результат замены всех вхождения строки searchString внутри строки subject на replacementString
// Если строка searchString пустая, то возвращается subject
string ReplaceString(const string& subject,
	const string& searchString, const string& replacementString)
{
	// Эта функция написана не до конца. Напишите недостающий код самостоятельно

	size_t position = 0;
	// Результат будет записан в новую строку result, оставляя строку subject неизменной
	// Какие преимущества есть у этого способа по сравнению с алгоритмом, выполняющим
	// замену прямо в строке subject?
	string result;

	if (searchString.length() == 0)
	{
		return subject;
	}

	while (position < subject.length())
	{
		// Находим позицию искомой строки, начиная с pos
		size_t foundPos = subject.find(searchString, position);

		// В результирующую строку записываем текст из диапазона [pos,foundPos)
		if (foundPos != string::npos)
		{
			result.append(subject, position, foundPos - position).append(replacementString);
			position = searchString.length() + foundPos;
		}
		else
		{
			result.append(subject, position);
			position = subject.length();
		}

	}
	return result;
}

void CopyFileWithReplacement(const string& inputFileName, const string& outputFileName,
	const string& searchString, const string& replacementString)
{
	ifstream input = OpenInputFileStream(inputFileName);
	
	ofstream output = OpenOutputFileStream(outputFileName);
	
	string line;
	string result;

	while (getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << endl;

		if (!output.flush()) // Если не удалось сбросить данные на диск
		{
			throw std::exception("Failed to save data on disk");
		}	
	}
}

int main(int argc, char* argv[])
{
	try
	{
		Args args = ParseArgs(argc, argv);

		CopyFileWithReplacement(args.inputFileName, args.outputFileName, args.searchString, args.replaceString);
	}
	catch (const std::exception& exception)
	{
		std::cout << ConcatStringWithMessage(exception.what());

		return 1;
	}
	
}