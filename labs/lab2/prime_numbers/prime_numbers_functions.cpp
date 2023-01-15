#include "./prime_numbers_functions.h"

void PrintSet(const std::set<int>& primeNumbers)
{
	if (primeNumbers.empty())
	{
		std::cout << "No prime numbers!";
	}

	std::for_each(primeNumbers.begin(), primeNumbers.end(), [](const int& number) {
		std::cout << number << "\t";
	});

	std::cout << std::endl;
}

std::set<int> GeneratePrimeNumbersSet(const int upperBound)
{
	std::set<int> primeNumbers;

	if (upperBound < 2)
	{
		return {};
	}

	primeNumbers.insert(primeNumbers.end(), 2);

	std::vector<bool> signPrime(upperBound + 1, true);

	for (int i = 3; i <= upperBound; i += 2)
	{
		if (signPrime[i])
		{
			primeNumbers.insert(primeNumbers.end(), i);

			for (int j = i + i; j <= upperBound; j += i) // тут, похоже, ошибка. Ќадо написать тест, который бы ее воспроизвел +
			{
				// if (signPrime[j]) можно убрать +
				signPrime[j] = false;
			}
		}
	}

	return primeNumbers;
}