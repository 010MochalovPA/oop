#include "polish_notation.h"

int main(int argc, char* argv[])
{
	try
	{
		std::string line;

		while (getline(std::cin, line))
		{
			std::stringstream inputstream(line);
			std::cout << CalculatePolishExpressionFromStream(inputstream) << std::endl;
		}

		return 0;
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;

		return 1;
	}
}