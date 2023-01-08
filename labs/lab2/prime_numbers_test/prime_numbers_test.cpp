#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../prime_numbers/prime_numbers.h"

TEST_CASE("Testing upperBound = 100000000 ")
{
	CHECK(GeneratePrimeNumbersSet(100000000).size() == 5761455);
}

TEST_CASE("Testing isNumber function")
{
	CHECK(isUnsignedNumber("abc") == false);
	CHECK(isUnsignedNumber("a123") == false);
	CHECK(isUnsignedNumber("123") == true);
}

TEST_CASE("Some default tests")
{
	CHECK(GeneratePrimeNumbersSet(0).size() == 0);

	CHECK(GeneratePrimeNumbersSet(1).size() == 0);

	CHECK(GeneratePrimeNumbersSet(2).size() == 1);

	CHECK(GeneratePrimeNumbersSet(100).size() == 25);
}