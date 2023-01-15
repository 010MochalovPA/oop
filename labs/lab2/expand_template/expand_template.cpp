#include "expand_template.h"

int main(int argc, char* argv[])
{
	std::optional<Args> optionalArgs = GetArgs(argc, argv);

	if (!optionalArgs.has_value())
	{
		std::cout << "Invalid value! Usege: expand_template.exe <input-file> <output-file> [<param> <value> [<param> <value> …]]" << std::endl;
		return 1;
	}

	Args args = optionalArgs.value();

	std::ifstream input(args.inputFileName);

	if (!input.is_open())
	{
		std::cout << "Failed to open " << args.inputFileName << " for reading" << std::endl;
		return 1;
	}

	std::ofstream output(args.outputFileName);

	if (!output.is_open())
	{
		std::cout << "Failed to open " << args.outputFileName << " for writing" << std::endl;
		return 1;
	}

	std::vector<Node> bohr;
	
	Bohr_init(bohr);

	AddNodesFromMap(bohr, args.params);

	InitLinksOnBohr(bohr);

	std::string line;

	while (getline(input, line))
	{
		output << ExpandTemplate(bohr, line, args.params);
	}

	return 0;
}
