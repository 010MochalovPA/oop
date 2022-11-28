#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct Args
{
	string inputFileName;
	string searchText;
};

Args ParseArgs(const int&, char*[]);
ifstream OpenInputFileStream(const string&);
void PrintLineIndex(const int&);
int FindLineIndex(istream& /*sourceStream*/, string& /*searchString*/, void (*callback)(const int&));
string JoinExceptionString(const string&);

string JoinExceptionString(const string& exception)
{
	return exception + '\n'
		+ "Usage: findtext.exe <file name> <text to search>" + '\n';
}

ifstream OpenInputFileStream(const string& fileName)
{
	ifstream input(fileName, ios::binary);

	if (!input.is_open())
	{
		throw "Failed to open <input file> for reading";
	}

	return input;
}

Args ParseArgs(const int& argc, char* argv[])
{
	if (argc != 3)
	{
		throw "Invalid argument count";
	}

	Args args = {};
	args.inputFileName = argv[1];
	args.searchText = argv[2];

	return args;
}

void PrintLineIndex(const int& lineIndex)
{
	cout << lineIndex << endl;
}

int FindLineIndex(istream& sourceStream, string& searchString, void (*callback)(const int&))
{
	string sourceLine;
	bool isFound = false;

	for (int lineIndex = 1; getline(sourceStream, sourceLine); ++lineIndex)
	{
		size_t index = sourceLine.find(searchString);
		if (index != string::npos)
		{
			isFound = true;
			callback(lineIndex);
		}
	}
	return isFound;
}

int main(int argc, char* argv[])
{

	try
	{
		Args args = ParseArgs(argc, argv);

		ifstream input = OpenInputFileStream(args.inputFileName);

		if (!FindLineIndex(input, args.searchText, PrintLineIndex))
		{
			cout << "No string found" << endl;
			return 1;
		}

		return 0;
	}
	catch (const char* exception)
	{
		cout << JoinExceptionString(exception);
		return 1;
	}

}