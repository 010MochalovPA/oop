#include "prime_numbers.h"

std::optional<int> getArgs(int argc, char* argv[])
{
	
	if (argc != 2 || !isUnsignedNumber(argv[1]))
	{
		return std::nullopt;
	}

	int upperBound = std::stoi(argv[1]);

	if (upperBound < 0 || upperBound > 100000000)
	{
		return std::nullopt;
	}

	return  { upperBound };
}

int main(int argc, char* argv[])
{
	std::optional<int> upperBound = getArgs(argc, argv);

	if (!upperBound.has_value())
	{
		std::cout << "Invalid input! Usage:prime_numbers.exe <number>" << std::endl;
		return 1;
	}

	std::set PrimeNumbers = GeneratePrimeNumbersSet(upperBound.value());
	
	PrintSet(PrimeNumbers);
	
	return 0;
}
