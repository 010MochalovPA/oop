#include "prime_numbers_functions.h"

std::optional<int> GetUpperBound(int argc, char* argv[]) // с маленькой буквы возвращает не то, как называется +
{
	
	if (argc != 2) // isUnsignetNumber выпилить +
	{
		return std::nullopt;
	}

	int upperBound = std::stoi(argv[1]); // разобраться со stoi +

	if (upperBound < 0 || upperBound > 100000000)
	{
		return std::nullopt;
	}

	return  { upperBound };
}

int main(int argc, char* argv[])
{
	try
	{
		std::optional<int> upperBound = GetUpperBound(argc, argv);

		if (!upperBound.has_value())
		{
			std::cout << "Invalid input! Usage: prime_numbers.exe <number>" << std::endl;
			return 1;
		}

		// название переменной с маленькой +
		std::set primeNumbers = GeneratePrimeNumbersSet(upperBound.value());

		PrintSet(primeNumbers);

		return 0;
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
	}
	
}
