#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../vector_headers.h"

TEST_CASE("Testing a function for an correct value")
{
	std::istringstream input("-1 2 8 3 -1.40 -3");
	std::ostringstream output("");
	// -1.000 2.000 8.000 3.000 -1.400 -3.000
	GetAndTransformVector(input, output, MultiplyNegativeElementsOnProductMinAndMax);
	// max 8.000
	// min -3.000
	// min * max = -24.000
	// -1.000 * -24.000 = 24.000
	// -1.400 * -24.000 = 33.600
	// -3.000 * -24.000 = 72.000
	// 24.000 2.000 8.000 3.000 36.600 72.000
	// sorded: 2.000 3.000 8.000 24.000 33.600 72.000
	CHECK(output.str() == "2.000 3.000 8.000 24.000 33.600 72.000 \n");
}

TEST_CASE("Testing a function for an correct value 2")
{
	std::istringstream input("-2.4 -2 8.25 3 2.40 4");
	std::ostringstream output("");
	// -2.400 -2.000 8.250 3.000 2.400 4.000
	GetAndTransformVector(input, output, MultiplyNegativeElementsOnProductMinAndMax);
	// max 8.250
	// min -2.400
	// min * max = -19.800
	// -2.000 * -19.800 = 39.600
	// -2.400 * -19.800 = 47.520
	// 47.520 39.600 8.250 3.000 2.400 4.000
	// sorded: 2.400 3.000 4.000 8.250 39.600 47.520
	CHECK(output.str() == "2.400 3.000 4.000 8.250 39.600 47.520 \n");
}

TEST_CASE("Testing a function for an empty value")
{
	std::istringstream input("");
	std::ostringstream output("");
	
	GetAndTransformVector(input, output, MultiplyNegativeElementsOnProductMinAndMax);
	
	CHECK(output.str() == "");
}

TEST_CASE("Testing a function for an incorrect value")
{
	std::istringstream input("-2 a 35");
	std::ostringstream output("");

	GetAndTransformVector(input, output, MultiplyNegativeElementsOnProductMinAndMax);

	CHECK(output.str() == "");
}