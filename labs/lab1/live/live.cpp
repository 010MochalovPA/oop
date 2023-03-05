#include <iostream>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
};

Args ParseArgs(const int& argc, char* argv[])
{
	if (argc < 2)
	{
		throw std::invalid_argument("Invalid argument count");
	}

	Args args = {};

	
	args.inputFileName = argv[1];
	args.outputFileName = argv[2] ? argv[2] : "cout";

	if (args.inputFileName.empty() || args.outputFileName.empty())
	{
		throw std::invalid_argument("Invalid argument");
	}

	return args;
}

int main()
{
	try
	{
	    
	}
	catch (const std::exception&)
	{
	
	}
}