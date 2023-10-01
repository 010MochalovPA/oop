#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Calculator/Calculator.h"

TEST_CASE("Create var")
{
	GIVEN("Calculator")
	{
		Calculator calc;

		WHEN("empty calc")
		{
			REQUIRE(calc.GetVariables().empty());
			REQUIRE(calc.GetFunctions().empty());
		}

		WHEN("incorrect create var")
		{
			REQUIRE(calc.CreateVar("1abc", "12"));
			REQUIRE(!calc.CreateVar("1abc", "12"));
		}

		WHEN("correct create var")
		{
			REQUIRE(calc.CreateVar("Abc", "NAN"));
			
			THEN("Abc has value Nan")
			{
				REQUIRE(std::isnan(calc.GetIdentifierValue("Abc")));
			}
			THEN("try create second same Identifier")
			{
				REQUIRE(!calc.CreateVar("Abc", "NAN"));
			}
		}
	}
}

TEST_CASE("Create let")
{
	GIVEN("Calculator")
	{
		Calculator calc;

		WHEN("correct create let")
		{
			REQUIRE(calc.CreateVar("Abc", "NAN"));

			THEN("Abc has value Nan")
			{
				REQUIRE(std::isnan(calc.GetIdentifierValue("Abc")));
			}

			REQUIRE(calc.AssignLet("Abc", "1.23"));

			THEN("Abc has value 1.23")
			{
				REQUIRE(1.23 == calc.GetIdentifierValue("Abc"));
			}

			REQUIRE(calc.CreateVar("x", "NAN"));
			REQUIRE(calc.AssignLet("x", "-2"));

			THEN("x has value -2")
			{
				REQUIRE(-2 == calc.GetIdentifierValue("x"));
			}

			REQUIRE(calc.AssignLet("Abc", "x"));

			THEN("Abc has value -2")
			{
				REQUIRE(-2 == calc.GetIdentifierValue("Abc"));
			}

			REQUIRE(calc.AssignLet("Abc", "1"));

			THEN("Abc has value 1")
			{
				REQUIRE(1 == calc.GetIdentifierValue("Abc"));
			}

			REQUIRE(!calc.AssignLet("Abc", "zz"));
		}

	}
}

TEST_CASE("Creating unary functions")
{
	GIVEN("Calculator")
	{
		Calculator calc;

		REQUIRE(calc.CreateVar("x", "NAN"));
		REQUIRE(calc.CreateVar("y", "NAN"));
		REQUIRE(calc.AssignLet("z", "20.20"));

		WHEN("correct create fn")
		{
			REQUIRE(calc.CreateUnaryFunction("f", "z"));
			REQUIRE(20.20 == calc.GetIdentifierValue("f"));
			REQUIRE(calc.CreateUnaryFunction("f1", "x"));
			REQUIRE(std::isnan(calc.GetIdentifierValue("f1")));
		}
	
		WHEN("incorrect create fn")
		{
			REQUIRE(!calc.CreateUnaryFunction("f", "func4"));
			REQUIRE(!calc.CreateUnaryFunction("f1", "func5"));
		}

		WHEN("changing variable")
		{
			REQUIRE(calc.AssignLet("y", "8.20"));
			REQUIRE(calc.CreateUnaryFunction("f3", "y"));
			REQUIRE(8.20 == calc.GetIdentifierValue("f3"));
			REQUIRE(calc.AssignLet("y", "6.40"));
			REQUIRE(6.40 == calc.GetIdentifierValue("f3"));
		}
	}
}


TEST_CASE("Creating binary functions")
{
	GIVEN("Calculator")
	{
		Calculator calc;

		REQUIRE(calc.CreateVar("x", "NAN"));
		REQUIRE(calc.CreateVar("y", "4"));
		REQUIRE(calc.AssignLet("z", "20.20"));

		BinaryFn fn = [](double a, double b) { return a / b; };

		WHEN("correct create fn")
		{
			REQUIRE(calc.CreateBinaryFunction("f", "z", "y", fn));
			REQUIRE(5.05 == calc.GetIdentifierValue("f"));
			REQUIRE(calc.CreateUnaryFunction("f1", "x"));
			REQUIRE(std::isnan(calc.GetIdentifierValue("f1")));
		}

		WHEN("incorrect create fn")
		{
			REQUIRE(!calc.CreateBinaryFunction("f", "func4", "x", fn));
			REQUIRE(!calc.CreateBinaryFunction("f1", "x", "func5", fn));
			REQUIRE(!calc.CreateBinaryFunction("f1", "x", "5", fn));
		}
		
		WHEN("changing variable")
		{
			REQUIRE(calc.AssignLet("y", "8"));
			REQUIRE(calc.CreateBinaryFunction("f3", "z", "y", fn));
			REQUIRE(2.525 == calc.GetIdentifierValue("f3"));
			REQUIRE(calc.AssignLet("y", "2"));
			REQUIRE(10.10 == calc.GetIdentifierValue("f3"));
		}
	}
}