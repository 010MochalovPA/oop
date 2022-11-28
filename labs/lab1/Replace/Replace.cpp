#include <fstream>
#include <string>
#include <iostream>

using namespace std;
void CloseStreams(ifstream& input, ofstream& output);

string ReplaceString(const string& subject,
	const string& searchString, const string& replacementString);

void CopyStreamWithReplacement(istream& input, ostream& output,
	const string& searchString, const string& replacementString);

int CopyFileWithReplacement(const string& inputFileName, const string& outputFileName,
	const string& searchString, const string& replacementString);


void CloseStreams(ifstream& input, ofstream& output)
{
	input.close();
	output.close();
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

void CopyStreamWithReplacement(istream& input, ostream& output,
	const string& searchString, const string& replacementString)
{
	string line;

	while (getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << endl;
	}
}

int CopyFileWithReplacement(const string& inputFileName, const string& outputFileName,
	const string& searchString, const string& replacementString)
{
	ifstream input(inputFileName);
	
	if (!input.is_open())
	{
		cout << "Failed to open " << inputFileName << " for reading" << endl;
		return 1;
	}

	ofstream output(outputFileName);

	if (!output.is_open())
	{
		cout << "Failed to open " << outputFileName << " for writing" << endl;
		return 1;
	}
	
	string line;

	while (getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << endl;

		if (!output.flush()) // Если не удалось сбросить данные на диск
		{
			cout << "Failed to save data on disk" << endl;
			return 1;
		}
		
	}

	CloseStreams(input, output);
	return 0;
	
}

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		cout << "Invalid argument count" << endl
			 << "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>" << endl;
		return 1;
	}

	// Самостоятельно выделите код копирования содержимого файла в отдельную функцию CopyFileWithReplacement, ??????
	// принимающую имена файлов, а также строки для поиска и замены
	// Добавьте обработку ошибок

	string inputFileName = argv[1];
	string outputFileName = argv[2];
	string searchString = argv[3];
	string replaceString = argv[4];


	return CopyFileWithReplacement(inputFileName, outputFileName, searchString, replaceString);
	
}