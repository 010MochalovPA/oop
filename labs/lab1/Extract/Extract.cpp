#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const unsigned int RADIX = 10;
const unsigned int MAX_INT = numeric_limits<unsigned int>::max();

struct Args
{
	string inputFileName;
	string outputFileName;
	size_t startPosition;
	int fragmentSize;
};

void ExtractFragmentFromFile(const string& /*inputFileName*/, const string& /*outputFileName*/, const size_t& /*startPosition*/, const int& /*fragmentSize*/);
string JoinExceptionString(const string&);
ifstream OpenInputFileStream(const string&);
ofstream OpenOutputFileStream(const string&);
size_t GetSizeOfFile(ifstream&);
void ThrowExceptionForInvalidFragment(const size_t&, const size_t&, const int&);
void ThrowExceptionForBadFlushOutput(ofstream&);
Args ParseArgs(const int&, char*[]);
void ThrowExceptionForOverflowInt(unsigned int, unsigned int);
void ThrowExceptionForNonNumericValue(const string&);
unsigned int ConvertStringToInt(const string&);

void ThrowExceptionForOverflowInt(unsigned int a, unsigned int b)
{
	if (MAX_INT - a < b)
	{
		throw "Incorrect start position or fragment size";
	}
}

void ThrowExceptionForNonNumericValue(const string& value)
{
	for (char ch : value)
	{
		if (!isdigit(ch))
		{
			throw "Incorrect start position or fragment size";
		}
	}
}

unsigned int ConvertStringToInt(const string& value)
{
	ThrowExceptionForNonNumericValue(value);

	unsigned int result = 0;

	for (char ch : value)
	{
		ThrowExceptionForOverflowInt(result * RADIX, ch - '0');

		result = (result * RADIX) + (ch - '0');
	}

	return result;
}

Args ParseArgs(const int& argc, char* argv[])
{
	if (argc != 5)
	{
		throw "Invalid argument count";
	}

	Args args = {};

	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.startPosition = (size_t)ConvertStringToInt(argv[3]);
	args.fragmentSize = ConvertStringToInt(argv[4]);

	return args;
}

void ThrowExceptionForBadFlushOutput(ofstream& output)
{
	if (!output.flush())
	{
		cout << "Failed to save data on disk" << endl;
	}
}

void ThrowExceptionForInvalidFragment(const size_t& sizeFile, const size_t& startPosition, const int& fragmentSize)
{
	if (startPosition < 0 || fragmentSize < 0)
	{
		throw "Incorrect start position or fragment size";
	}

	if (sizeFile < startPosition + fragmentSize)
	{
		throw "Invalid extractable fragment";
	}
}

size_t GetSizeOfFile(ifstream& input)
{
	input.seekg(0, ios::end);
	size_t sizeFile = input.tellg();
	input.seekg(0, ios::beg);

	return sizeFile;
}

string JoinExceptionString(const string& exception)
{
	return exception + '\n'
		+ "Usage: extract.exe <input file> <output file> <start position> <fragment size>" + '\n';
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

ofstream OpenOutputFileStream(const string& fileName)
{
	ofstream output(fileName, ios::binary);

	if (!output.is_open())
	{
		throw "Failed to open one of the files for writing";
	}

	return output;
}

void ExtractFragmentFromFile(const string& inputFileName, const string& outputFileName, const size_t& startPosition, const int& fragmentSize)
{
	ifstream input = OpenInputFileStream(inputFileName);
	
	ofstream output = OpenOutputFileStream(outputFileName);

	size_t sizeFile = GetSizeOfFile(input);

	ThrowExceptionForInvalidFragment(sizeFile, startPosition, fragmentSize);

	input.seekg(startPosition, ios::beg);

	for (size_t position = startPosition; position < startPosition + fragmentSize; ++position)
	{
		char ch;

		input.read(&ch, sizeof(ch));
		output.write(&ch, sizeof(ch));

		ThrowExceptionForBadFlushOutput(output);
	}
	
}


int main(int argc, char* argv[])
{

	try
	{
		Args args = ParseArgs(argc, argv);

		ExtractFragmentFromFile(args.inputFileName, args.outputFileName, args.startPosition, args.fragmentSize);
		
		return 0;
	}
	catch (const char* exception)
	{
		cout << JoinExceptionString(exception);
		return 1;
	}

}