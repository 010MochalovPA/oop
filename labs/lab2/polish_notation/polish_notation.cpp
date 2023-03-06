#include "polish_notation.h"
#include <sstream>

int main(int argc, char* argv[])
{
	try
	{
		std::string line;

		while (getline(std::cin, line))
		{
			std::stringstream inputstream(line);
			int result = CalculatePolishExpressionFromStream(inputstream);

			std::cout << result << std::endl;
		}

		return 0;
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;

		return 1;
	}
}