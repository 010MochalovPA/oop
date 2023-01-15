#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../prime_numbers/prime_numbers_functions.h"

TEST_CASE("Testing upperBound = 100000000 ")
{
	CHECK(GeneratePrimeNumbersSet(100000000).size() == 5761455);
}

TEST_CASE("Some default tests")
{
	CHECK(GeneratePrimeNumbersSet(0).size() == 0);

	CHECK(GeneratePrimeNumbersSet(1).size() == 0);

	CHECK(GeneratePrimeNumbersSet(2) == std::set<int>{ 2 });

	CHECK(GeneratePrimeNumbersSet(100) == std::set<int>{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 });

	CHECK(GeneratePrimeNumbersSet(21) == std::set<int>{ 2, 3, 5, 7, 11, 13, 17, 19 });  // нужно проверять не кол-во а состав
}