#include <fstream>
#include <iostream>
#include <string>

using namespace std;
void PrintLineIndex(int);
bool CompareFiles(ifstream&, ifstream&, void (*callback)(int));
void ThrowExceptionForInvalidCountArgs(const int&);
void ThrowExceptionForUnopenedStreams(ifstream&, ifstream&);

string JoinExceptionString(const string& exception)
{
	return exception + '\n'
		+ "Usage: compare.exe <file1> <file2>" + '\n';
}

void ThrowExceptionForUnopenedStreams(ifstream& input1, ifstream& input2)
{
	if (!input1.is_open() || !input2.is_open())
	{
		throw "Failed to open one of the files for reading";
	}
}

void ThrowExceptionForInvalidCountArgs(const int& argc)
{
	if (argc != 3)
	{
		throw "Invalid argument count";
	}
}

void PrintLineIndex(int lineIndex)
{
	cout << "Files are different. Line number is " << lineIndex << endl;
}

bool CompareFiles(ifstream& input1, ifstream& input2, void (*callback)(int))
{
	string rowFile1, rowFile2;

	for (int lineIndex = 1; !input1.eof(); ++lineIndex)
	{
		getline(input1, rowFile1);
		getline(input2, rowFile2);

		if ((rowFile1 != rowFile2) || (input1.eof() != input2.eof()))
		{
			callback(lineIndex);

			return true;
		}
	}

	return false;
}

int main(int argc, char* argv[])
{
	try
	{
		ThrowExceptionForInvalidCountArgs(argc);

		ifstream input1(argv[1]), input2(argv[2]);

		ThrowExceptionForUnopenedStreams(input1, input2);

		if (!CompareFiles(input1, input2, PrintLineIndex))
		{
			cout << "Files are equal" << endl;
			return 0;
		}

		return 1;
	}
	catch (const char* exception)
	{
		cout << JoinExceptionString(exception);
		return 1;
	}
}