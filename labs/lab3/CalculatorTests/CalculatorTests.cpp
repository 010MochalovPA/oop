#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Calculator/CCalculator.h"

TEST_CASE("Create var")
{
	GIVEN("Calculator")
	{
		CCalculator calc;

		WHEN("empty calc")
		{
			REQUIRE(calc.GetVariables().empty());
			REQUIRE(calc.GetFunctions().empty());
		}

		WHEN("incorrect create var")
		{
			REQUIRE(!calc.CreateVar("1abc"));
			REQUIRE(!calc.CreateVar("_"));
			REQUIRE(!calc.CreateVar("123"));
		}

		WHEN("correct create var")
		{
			REQUIRE(calc.CreateVar("Abc"));
			
			THEN("Abc has value Nan")
			{
				REQUIRE(std::isnan(calc.GetIdentifierValue("Abc")));
			}
		}

		WHEN("try create second same Identifier")
		{
			REQUIRE(calc.CreateVar("Abc"));
			REQUIRE(!calc.CreateVar("Abc"));
		}
	}
}

TEST_CASE("Create let")
{
	GIVEN("Calculator")
	{
		CCalculator calc;

		WHEN("correct create let")
		{
			REQUIRE(calc.CreateVar("Abc"));

			THEN("Abc has value Nan")
			{
				REQUIRE(std::isnan(calc.GetIdentifierValue("Abc")));
			}

			REQUIRE(calc.CreateLet("Abc", "1.23"));

			THEN("Abc has value 1.23")
			{
				REQUIRE(1.23 == calc.GetIdentifierValue("Abc"));
			}

			REQUIRE(calc.CreateVar("x"));
			REQUIRE(calc.CreateLet("x", "-2"));

			THEN("x has value -2")
			{
				REQUIRE(-2 == calc.GetIdentifierValue("x"));
			}

			
			REQUIRE(calc.CreateLet("Abc", "x"));

			THEN("Abc has value -2")
			{
				REQUIRE(-2 == calc.GetIdentifierValue("Abc"));
			}

			REQUIRE(calc.CreateLet("Abc", "1"));

			THEN("Abc has value 1")
			{
				REQUIRE(1 == calc.GetIdentifierValue("Abc"));
			}

			REQUIRE(!calc.CreateLet("Abc", "zz"));
		}

	}
}

TEST_CASE("Creating functions")
{
	GIVEN("Calculator")
	{
		CCalculator calc;

		REQUIRE(calc.CreateVar("x"));
		REQUIRE(calc.CreateVar("y"));
		REQUIRE(calc.CreateLet("z", "20.20"));

		WHEN("correct create fn")
		{
			CCalculator::Function func1 = { "f", "z", "0", CCalculator::OPERATION::Addition };
			REQUIRE(calc.CreateFunction("f", func1));
			REQUIRE(20.20 == calc.GetIdentifierValue("f"));
			CCalculator::Function func2 = { "f", "x", "0", CCalculator::OPERATION::Addition };
			REQUIRE(calc.CreateFunction("f1", func2));
			REQUIRE(std::isnan(calc.GetIdentifierValue("f1")));
		}
	
		WHEN("changing variable")
		{
			REQUIRE(calc.CreateLet("y", "8.20"));
			CCalculator::Function func3 = { "f3", "y", "2", CCalculator::OPERATION::Division };
			REQUIRE(calc.CreateFunction("f3", func3));
			REQUIRE(4.10 == calc.GetIdentifierValue("f3"));
			REQUIRE(calc.CreateLet("y", "6.40"));
			REQUIRE(3.20 == calc.GetIdentifierValue("f3"));
		}
	}
}