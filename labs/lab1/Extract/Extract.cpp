#include <fstream>
#include <iostream>
#include <string>

const unsigned int RADIX = 10;

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	size_t startPosition;
	int fragmentSize;
};

void ExtractFragmentFromFile(const std::string& /*inputFileName*/, const std::string& /*outputFileName*/, const size_t& /*startPosition*/, const int& /*fragmentSize*/);
size_t GetSizeOfFile(std::ifstream&);
Args ParseArgs(const int&, char*[]);
int SafeMultiply(int a, int b);
int SafeAdd(int a, int b);
unsigned int ConvertStringToInt(const std::string& value);

int SafeMultiply(int a, int b)
{
	if (a > 0 && b > 0 && a > (INT_MAX / b))
	{
		throw std::overflow_error("Invalid argument");
	}

	if (a > 0 && b < 0 && b < (INT_MIN / a))
	{
		throw std::overflow_error("Invalid argument");
	}

	if (a < 0 && b > 0 && a < (INT_MIN / b))
	{
		throw std::overflow_error("Invalid argument");
	}

	if (a < 0 && b < 0 && b < (INT_MAX / a))
	{
		throw std::overflow_error("Invalid argument");
	}
	return a * b;
}

int SafeAdd(int a, int b)
{
	if (b > 0 && a > (INT_MAX - b))
	{
		throw std::overflow_error("Invalid argument");
	}

	if (b < 0 && a < (INT_MAX - b))
	{
		throw std::overflow_error("Invalid argument");
	}

	return a + b;
}



unsigned int ConvertStringToInt(const std::string& value)
{
	for (char ch : value)
	{
		if (!isdigit(ch))
		{
			throw std::invalid_argument("Invalid argument");
		}
	}

	int result = 0;

	for (char ch : value)
	{
		result = SafeAdd(SafeMultiply(result, RADIX), ch - '0');
	}

	return result;
}

Args ParseArgs(const int& argc, char* argv[])
{
	if (argc != 5)
	{
		throw std::invalid_argument("Invalid argument count");
	}

	Args args = {};

	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.startPosition = (size_t)ConvertStringToInt(argv[3]);
	args.fragmentSize = ConvertStringToInt(argv[4]);

	return args;
}

size_t GetSizeOfFile(std::ifstream& input)
{
	input.seekg(0, std::ios::end);
	size_t sizeFile = input.tellg();
	input.seekg(0, std::ios::beg);

	return sizeFile;
}
// не передавать приметивные объекты по ссылке
void ExtractFragmentFromFile(const std::string& inputFileName, const std::string& outputFileName, const size_t& startPosition, const int& fragmentSize)
{
	std::ifstream input(inputFileName, std::ios::binary);

	if (!input.is_open())
	{
		throw std::invalid_argument("Failed to open <input file> for reading");
	}
	
	std::ofstream output(outputFileName, std::ios::binary);

	if (!output.is_open())
	{
		throw std::invalid_argument("Failed to open one of the files for writing");
	}
	//size_t не нужно проверять
	if (fragmentSize < 0)
	{
		throw std::invalid_argument("Incorrect fragment size");
	}

	size_t sizeFile = GetSizeOfFile(input);

	if (sizeFile < startPosition + fragmentSize)
	{
		throw std::invalid_argument("Invalid extractable fragment");
	}

	input.seekg(startPosition, std::ios::beg);

	for (size_t position = startPosition; position < startPosition + fragmentSize; ++position)
	{
		char ch;

		input.read(&ch, sizeof(ch));
		output.write(&ch, sizeof(ch));

		if(!output.flush())
		{
			throw std::invalid_argument("Failed to save data on disk");
		}
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
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		std::cout << "Usage: extract.exe <input file> <output file> <start position> <fragment size>" << std::endl;
		return 1;
	}
}